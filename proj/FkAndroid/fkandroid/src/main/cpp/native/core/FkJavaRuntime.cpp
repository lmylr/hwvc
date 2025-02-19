/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#include "FkJavaRuntime.h"
#include "FkDefinition.h"
#include "FkThread.h"

#define TAG "FkJavaRuntime"

FK_IMPL_CLASS_TYPE(FkJavaRuntime, FkObject)

FkJavaRuntime *FkJavaRuntime::instance = new FkJavaRuntime();
pthread_key_t FkJavaRuntime::threadKey = 0;
const int FkJavaRuntime::VERSION = JNI_VERSION_1_6;

FkJavaRuntime &FkJavaRuntime::getInstance() {
    return *instance;
}

void FkJavaRuntime::jniThreadDestroy(void *envPtr) {
    JNIEnv *env = static_cast<JNIEnv *>(envPtr);
    if (env != NULL) {
        FkJavaRuntime::getInstance().detachThread();
        pthread_setspecific(threadKey, NULL);
        FkLogI(TAG, "Destroy jni env: thread id=%p, env=%p", FkThread::currentThreadId(), env);
    }
}

bool FkJavaRuntime::jniRegister(JNIEnv *env, const char *clsName, const JNINativeMethod *methods, int len) {
    if (env == nullptr) {
        FkLogE(TAG, "[FAIL] JNIEnv is null.");
        return false;
    }
    jclass cls = env->FindClass(clsName);
    if (cls == nullptr) {
        FkLogE(TAG, "[FAIL] Class %s not found.", clsName);
        return false;
    }
    auto ret = env->RegisterNatives(cls, methods, len) == JNI_OK;
    env->DeleteLocalRef(cls);
    if (!ret) {
        FkLogE(TAG, "[FAIL] Class %s register fail.", clsName);
    } else {
        FkLogD(TAG, "[ OK ] Class %s register success.", clsName);
    }
    return ret;
}

FkJavaRuntime::FkJavaRuntime() : FkObject() {
}

FkJavaRuntime::~FkJavaRuntime() {
}

void FkJavaRuntime::attach(JavaVM *vm) {
    this->jvm = vm;
    if (pthread_key_create(&threadKey, jniThreadDestroy) != JNI_OK) {
        FkLogE(TAG, "Create jni thread key fail.");
    }
}

void FkJavaRuntime::detach() {
    pthread_key_delete(threadKey);
    JNIEnv *env = nullptr;
    jvm->GetEnv(reinterpret_cast<void **>(&env), VERSION);
    this->jvm = nullptr;
    if (nullptr == env) {
        FkLogE(TAG, "detach failed.");
        return;
    }
}

bool FkJavaRuntime::attachThread() {
    if (!jvm) {
        FkLogE(TAG, "attachThread failed. Please call attach before.");
        return false;
    }
    int64_t id = FkThread::currentThreadId();
    FkAssert(0 != id, false);
    JNIEnv *pEnv = nullptr;
    if (findEnv(&pEnv)) {
        FkLogE(TAG, "attachThread failed. Do not attach repeat. currentThreadId=%d", id);
        return false;
    }
    if (nullptr == pEnv) {
        _attachThread(&pEnv);
    }
    return true;
}

bool FkJavaRuntime::_attachThread(JNIEnv **env) {
    JNIEnv *pEnv = nullptr;
    int status = jvm->AttachCurrentThread(&pEnv, NULL);
    if (status < 0) {
        FkLogE(TAG, "attachThreadfailed.");
        return false;
    }
    pthread_setspecific(threadKey, (void *) pEnv);
    int64_t id = FkThread::currentThreadId();
    std::lock_guard<std::mutex> guard(atxMtx);
    mEnvMap.insert(std::pair<int64_t, JNIEnv *>(id, pEnv));
    *env = pEnv;
    FkLogI(TAG, "Create jni env: thread id=%p, env=%p", FkThread::currentThreadId(), pEnv);
    return true;
}

void FkJavaRuntime::detachThread() {
    if (!jvm) {
        FkLogE(TAG, "detachThread failed. Please call attach before.");
        return;
    }
    JNIEnv *pEnv = nullptr;
    if (findEnv(&pEnv)) {
        int64_t id = FkThread::currentThreadId();
        FkAssert(0 != id, );
        FkLogD(TAG, "currentThreadId=%p", id);
        int status = jvm->DetachCurrentThread();
        if (status < 0) {
            FkLogI(TAG, "detachThread failed. currentThreadId=%p. status=%d", id, status);
        }
        std::lock_guard<std::mutex> guard(atxMtx);
        mEnvMap.erase(mEnvMap.find(id));
    } else {
        FkLogI(TAG, "detachThread failed. Env not found. currentThreadId=%p", FkThread::currentThreadId());
    }

}

bool FkJavaRuntime::findEnv(JNIEnv **env) {
    int64_t id = FkThread::currentThreadId();
    FkAssert(0 != id, false);
    std::unique_lock<std::mutex> guard(atxMtx);
    auto itr = mEnvMap.find(id);
    if (mEnvMap.end() == itr) {
        guard.unlock();
        JNIEnv *pEnv = nullptr;
        jvm->GetEnv(reinterpret_cast<void **>(&pEnv), VERSION);
        if (nullptr != pEnv) {
            *env = pEnv;
            return true;
        }
        return false;
    }
    *env = itr->second;
    return true;
}

bool FkJavaRuntime::findEnv2(JNIEnv **env) {
    int64_t id = FkThread::currentThreadId();
    FkAssert(0 != id, false);
    std::unique_lock<std::mutex> guard(atxMtx);
    auto itr = mEnvMap.find(id);
    if (mEnvMap.end() == itr) {
        guard.unlock();
        jvm->GetEnv(reinterpret_cast<void **>(env), VERSION);
        if (nullptr != *env) {
            return true;
        } else {
            FkLogI(TAG, "findEnv2 with attach thread");
            return _attachThread(env);
        }
    }
    *env = itr->second;
    return true;
}
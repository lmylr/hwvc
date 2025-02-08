/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: Alimin
* CREATE TIME: 2022-4-23 14:15:54
*/

#include "FkSurfaceTextureSource.h"
#include "FkJniStringUTF8.h"
#include "FkGLMatrix.h"
#include "FkGLDefinition.h"

FK_IMPL_CLASS_TYPE(FkSurfaceTextureSource, FkAbsImageSource)

FkSurfaceTextureSource::FkSurfaceTextureSource(jobject javaSource) : FkAbsImageSource() {
    this->matrix = std::make_shared<FkGLMatrix>();
    this->javaSource = std::make_unique<FkJniGlobalRef>(javaSource);
    JNIEnv *env = nullptr;
    if (FkJavaRuntime::getInstance().findEnv2(&env)) {
        jclass clazz = env->GetObjectClass(javaSource);
        midGetSize = env->GetMethodID(clazz, "getSize", "()[I");
        midOnCreate = env->GetMethodID(clazz, "onCreate", "(IJLjava/lang/String;)I");
        midOnDestroy = env->GetMethodID(clazz, "onDestroy", "()I");
        midOnRender = env->GetMethodID(clazz, "onRender", "(IJLjava/lang/String;)I");
        midGetMatrix = env->GetMethodID(clazz, "getTransformMatrix", "()[F");
        midGetTimestamp = env->GetMethodID(clazz, "getTimestampInNS", "()J");
    }
}

FkSurfaceTextureSource::~FkSurfaceTextureSource() {
    this->javaSource = nullptr;
}

FkResult FkSurfaceTextureSource::onCreate(int32_t arg0, int64_t arg1, const std::string &arg2) {
    JNIEnv *env = nullptr;
    lastRenderReqId = -1;
    if (FkJavaRuntime::getInstance().findEnv2(&env)) {
        FkJniStringUTF8 str(arg2);
        auto ret = env->CallIntMethod(javaSource->obj(), midOnCreate, arg0, arg1, str.str());
        _updateTransformMatrix(env);
        return ret;
    }
    return FK_INVALID_STATE;
}

FkResult FkSurfaceTextureSource::onDestroy() {
    JNIEnv *env = nullptr;
    if (FkJavaRuntime::getInstance().findEnv2(&env)) {
        return env->CallIntMethod(javaSource->obj(), midOnDestroy);
    }
    return FK_INVALID_STATE;
}

FkResult FkSurfaceTextureSource::onRender(int32_t arg0, int64_t arg1, const std::string &arg2) {
    if (arg1 == lastRenderReqId) {
        return FK_OK;
    }
    lastRenderReqId = arg1;
    JNIEnv *env = nullptr;
    if (FkJavaRuntime::getInstance().findEnv2(&env)) {
        _updateTransformMatrix(env);
        FkJniStringUTF8 str(arg2);
        return env->CallIntMethod(javaSource->obj(), midOnRender, arg0, arg1, str.str());
    }
    return FK_INVALID_STATE;
}

FkSize FkSurfaceTextureSource::getSize() {
    JNIEnv *env = nullptr;
    if (FkJavaRuntime::getInstance().findEnv2(&env)) {
        jintArray result = static_cast<jintArray>(env->CallObjectMethod(javaSource->obj(), midGetSize));
        if (result) {
            auto len = env->GetArrayLength(result);
            if (len == 2) {
                auto *ptr = env->GetIntArrayElements(result, NULL);
                return FkSize(ptr[0], ptr[1]);
            }
        }
    }
    return FkSize(0, 0);
}

std::shared_ptr<FkMatrix> FkSurfaceTextureSource::getTransformMatrix() {
    return matrix;
}

void FkSurfaceTextureSource::_updateTransformMatrix(JNIEnv *env) {
    jfloatArray result = static_cast<jfloatArray>(env->CallObjectMethod(javaSource->obj(),
                                                                        midGetMatrix));
    if (result && env->GetArrayLength(result) >= 16) {
        jfloat *ptr = env->GetFloatArrayElements(result, NULL);
        memcpy((void *) matrix->get(), ptr, 16 * sizeof(float));
    }
}

int64_t FkSurfaceTextureSource::getTimestampInNS() {
    JNIEnv *env = nullptr;
    if (FkJavaRuntime::getInstance().findEnv2(&env)) {
        jlong result = env->CallLongMethod(javaSource->obj(), midGetTimestamp);
        return result;
    }
    return 0;
}

FkTexDescription FkSurfaceTextureSource::getTexDescription() {
    FkTexDescription desc;
    desc.target = GL_TEXTURE_EXTERNAL_OES;
    return desc;
}

std::shared_ptr<FkBitmap> FkSurfaceTextureSource::toBitmap() {
    return nullptr;
}

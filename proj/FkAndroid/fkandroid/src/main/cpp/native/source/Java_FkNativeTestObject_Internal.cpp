//
// Created by Alimin on 2025/2/19.
//
#include "Java_FkNativeTestObject.h"
#include "FkJavaRuntime.h"

namespace Java_FkNativeTestObject {

    jlong nativeCreate(JNIEnv *env, jclass cls, jboolean arg0, jbyte arg1, jchar arg2, jshort arg3, jint arg4, jlong arg5, jfloat arg6, jdouble arg7, jstring arg8, jobject arg9, jbyteArray arg10) {
        return 0;
    }

    jint nativeDestroy(JNIEnv *env, jclass cls, jlong handle) {
        return 0;
    }

    bool reg(JNIEnv *env) {
        return FkJavaRuntime::jniRegister(env, CLASS_NAME, METHODS, METHODS_NUM);
    }

    const char *CLASS_NAME = "com/alimin/fk/source/FkNativeTestObject";

    const int METHODS_NUM = 2;

    const JNINativeMethod METHODS[] = {
            {"nativeCreate", "(ZBCSIJFDLjava/lang/String;Ljava/lang/Object;[B)J", (void *) nativeCreate},
            {"nativeDestroy", "(J)I", (void *) nativeDestroy},
    };

};
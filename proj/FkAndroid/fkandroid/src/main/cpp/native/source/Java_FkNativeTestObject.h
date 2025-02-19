//
// Created by Alimin on 2025/2/19.
//
#pragma once
#include <jni.h>

namespace Java_FkNativeTestObject {

  jlong nativeCreate(JNIEnv *env, jclass cls, jboolean arg0, jbyte arg1, jchar arg2, jshort arg3, jint arg4, jlong arg5, jfloat arg6, jdouble arg7, jstring arg8, jobject arg9, jbyteArray arg10);

  jint nativeDestroy(JNIEnv *env, jclass cls, jlong handle);

  bool reg(JNIEnv *env);

  extern const char *CLASS_NAME;

  extern const int METHODS_NUM;

  extern const JNINativeMethod METHODS[2];

};

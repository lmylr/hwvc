/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: Alimin
* CREATE TIME: 2022-4-23 14:15:54
*/

#include "FkJniStringUTF8.h"
#include "FkJavaRuntime.h"

FK_IMPL_CLASS_TYPE(FkJniStringUTF8, FkObject)

FkJniStringUTF8::FkJniStringUTF8(const std::string &str) : FkObject(), src(str) {
}

FkJniStringUTF8::~FkJniStringUTF8() {
    JNIEnv *env = nullptr;
    if (_str && FkJavaRuntime::getInstance().findEnv(&env)) {
        env->DeleteLocalRef(_str);
    }
}

jstring FkJniStringUTF8::str() {
    JNIEnv *env = nullptr;
    if (_str == nullptr && src != "" && FkJavaRuntime::getInstance().findEnv(&env)) {
        _str = env->NewStringUTF(src.c_str());
    }
    return _str;
}
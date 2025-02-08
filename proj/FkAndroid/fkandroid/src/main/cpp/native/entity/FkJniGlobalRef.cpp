/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns)

* CREATE TIME: 2022/4/10.
*/

#include "FkJniGlobalRef.h"
#include "FkJavaRuntime.h"

FK_IMPL_CLASS_TYPE(FkJniGlobalRef, FkObject)

FkJniGlobalRef::FkJniGlobalRef(jobject obj) : FkObject() {
    JNIEnv *env = nullptr;
    if (FkJavaRuntime::getInstance().findEnv(&env)) {
        _obj = env->NewGlobalRef(obj);
    }
}

FkJniGlobalRef::~FkJniGlobalRef() {
    JNIEnv *env = nullptr;
    if (FkJavaRuntime::getInstance().findEnv(&env)) {
        env->DeleteGlobalRef(_obj);
    }
}

jobject FkJniGlobalRef::obj() {
    return _obj;
}

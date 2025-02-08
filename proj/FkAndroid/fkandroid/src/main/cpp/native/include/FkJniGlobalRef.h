/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns)

* CREATE TIME: 2022/4/10.
*/

#ifndef FKANDROID_FKJNIGLOBALREF_H
#define FKANDROID_FKJNIGLOBALREF_H

#include "FkObject.h"
#include <jni.h>

FK_SUPER_CLASS(FkJniGlobalRef, FkObject) {
FK_DEF_CLASS_TYPE_FUNC(FkJniGlobalRef)

public:
    FkJniGlobalRef(jobject obj);

    FkJniGlobalRef(const FkJniGlobalRef &o) = delete;

    virtual ~FkJniGlobalRef();

    jobject obj();

private:
    jobject _obj = nullptr;
};


#endif //FKANDROID_FKJNIGLOBALREF_H

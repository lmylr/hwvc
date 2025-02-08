/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
* CREATE TIME: 2022-4-23 14:15:54
*/

#ifndef FKANDROID_FKJNISTRINGUTF8_H
#define FKANDROID_FKJNISTRINGUTF8_H

#include "FkObject.h"
#include <jni.h>

FK_SUPER_CLASS(FkJniStringUTF8, FkObject) {
FK_DEF_CLASS_TYPE_FUNC(FkJniStringUTF8)

public:
    FkJniStringUTF8(const std::string &str);

    FkJniStringUTF8(const FkJniStringUTF8 &o) = delete;

    virtual ~FkJniStringUTF8();

    jstring str();

private:
    std::string src = "";
    jstring _str = nullptr;

};


#endif //FKANDROID_FKJNISTRINGUTF8_H

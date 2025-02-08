/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: aliminabc@gmail.com

* CREATE TIME: 2024-06-09 16:36:25
*/

#ifndef FK_BASE_FKVALUE_H
#define FK_BASE_FKVALUE_H

#include "FkObject.h"

FK_SUPER_CLASS(FkValue, FkObject) {
FK_DEF_CLASS_TYPE_FUNC(FkValue)

public:
    FkValue();

    FkValue(const int32_t &value);

    FkValue(const int64_t &value);

    FkValue(const float &value);

    FkValue(const double &value);

    FkValue(const std::string &value);

    FkValue(const int32_t &int32Val, const int64_t &int64Val, const float &floatVal, const double &doubleVal, const std::string &strVal);

    FkValue(const FkValue &o);

    virtual ~FkValue();

    std::string getString();

    int32_t getInt32();

    int64_t getInt64();

    float getFloat();

    double getDouble();

    FkValue &operator=(const FkValue &value);

    FkValue &operator=(const int32_t &value);

    FkValue &operator=(const int64_t &value);

    FkValue &operator=(const float &value);

    FkValue &operator=(const double &value);

    FkValue &operator=(const std::string &value);

private:
    int32_t int32Val;
    int64_t int64Val;
    float floatVal;
    double doubleVal;
    std::string strVal;
};

#endif //FK_BASE_FKVALUE_H
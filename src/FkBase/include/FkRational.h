/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#ifndef FK_BASE_FKRATIONAL_H
#define FK_BASE_FKRATIONAL_H

#include "FkObject.h"
#include "FkRational.h"

FK_SUPER_CLASS(FkRational, FkObject) {
FK_DEF_CLASS_TYPE_FUNC(FkRational)

public:
    FkRational();

    FkRational(int32_t num, int32_t den);

    FkRational(const FkRational &o);

    ~FkRational();

    virtual FkRational &operator=(const FkRational &o);

    float toFloat();

    double toDouble();

public:
    int32_t num; ///< Numerator(分子)
    int32_t den; ///< Denominator(分母)
};


#endif //FK_BASE_FKRATIONAL_H

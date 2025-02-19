/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: Alimin
* CREATE TIME: 2022-3-27 17:09:52
*/

#ifndef FK_BASE_FKMATH_H
#define FK_BASE_FKMATH_H

#include "FkObject.h"
#include "FkIntVec2.h"
#include "FkDoubleVec2.h"
#include "FkRational.h"

class FkMath {
public:
    const static double PI;
    const static FkRational PI_R;

    virtual ~FkMath();

    static float distance(FkIntVec2 &p0, FkIntVec2 &p1);

    static double distance(FkDoubleVec2 &p0, FkDoubleVec2 &p1);

    static float cos(float radians);

    static float sin(float radians);

private:
    FkMath() = delete;

    FkMath(const FkMath &o) = delete;
};

#endif //FK_BASE_FKMATH_H
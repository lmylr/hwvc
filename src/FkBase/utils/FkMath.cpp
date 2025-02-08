/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: Alimin
* CREATE TIME: 2022-3-27 17:09:52
*/

#include "FkMath.h"
#include <cmath>

const double FkMath::PI = M_PI;
const FkRational FkMath::PI_R = {355, 113};

FkMath::~FkMath() {

}

float FkMath::distance(FkIntVec2 &p0, FkIntVec2 &p1) {
    return sqrt((p1.x - p0.x) * (p1.x - p0.x) + (p1.y - p0.y) * (p1.y - p0.y));
}

double FkMath::distance(FkDoubleVec2 &p0, FkDoubleVec2 &p1) {
    return sqrt((p1.x - p0.x) * (p1.x - p0.x) + (p1.y - p0.y) * (p1.y - p0.y));
}

float FkMath::cos(float radians) {
    return std::cos(radians);
}

float FkMath::sin(float radians) {
    return std::sin(radians);
}

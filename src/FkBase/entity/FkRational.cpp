/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#include "FkRational.h"

FK_IMPL_CLASS_TYPE(FkRational, FkObject)

FkRational::FkRational() : FkObject(), num(0), den(1) {

}

FkRational::FkRational(int32_t num, int32_t den) : FkObject(), num(num), den(den) {

}

FkRational::FkRational(const FkRational &o) : FkObject(), num(o.num), den(o.den) {

}

FkRational::~FkRational() {
    num = 0;
    den = 1;
}

FkRational &FkRational::operator=(const FkRational &o) {
    this->num = o.num;
    this->den = o.den;
    return *this;
}

float FkRational::toFloat() {
    if (0 == den) {
        return 0.0f;
    }
    return num / (float) den;
}

double FkRational::toDouble() {
    if (0 == den) {
        return 0.0;
    }
    return num / (double) den;
}

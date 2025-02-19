/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#include "FkMatrix.h"

FK_IMPL_CLASS_TYPE(FkMatrix, FkObject)

FkMatrix::FkMatrix() : FkObject() {

}

FkMatrix::FkMatrix(const FkMatrix &o) : FkObject(o) {

}

FkMatrix::~FkMatrix() {

}

std::string FkMatrix::toString() {
    return FkObject::toString();
}

bool FkMatrix::isZero() {
    return false;
}

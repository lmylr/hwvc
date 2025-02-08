/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#include "FkShape.h"

FK_IMPL_CLASS_TYPE(FkShape, FkObject)

FkShape::FkShape() : FkObject() {

}

FkShape::FkShape(const FkShape &o) : FkObject(o), type(o.type) {

}

FkShape::~FkShape() {

}

FkShape::kType FkShape::getType() {
    return type;
}
/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns)

* CREATE TIME: 2025-02-05 22:49:47
*/

#include "FkGravity.h"

FK_IMPL_CLASS_TYPE(FkGravity, FkObject)

const int FkGravity::AXIS_SPECIFIED = 0x0001;
const int FkGravity::AXIS_Y_SHIFT = 4;
const int FkGravity::AXIS_X_SHIFT = 0;
const int FkGravity::CENTER_VERTICAL = AXIS_SPECIFIED << AXIS_Y_SHIFT;
const int FkGravity::CENTER_HORIZONTAL = AXIS_SPECIFIED << AXIS_X_SHIFT;
const int FkGravity::CENTER = CENTER_VERTICAL | CENTER_HORIZONTAL;
const int FkGravity::LEFT = CENTER_VERTICAL | CENTER_HORIZONTAL;
const int FkGravity::TOP = CENTER_VERTICAL | CENTER_HORIZONTAL;
const int FkGravity::RIGHT = CENTER_VERTICAL | CENTER_HORIZONTAL;
const int FkGravity::BOTTOM = CENTER_VERTICAL | CENTER_HORIZONTAL;

FkGravity::FkGravity() : FkObject() {

}

FkGravity::FkGravity(const FkGravity &o) : FkObject(o) {

}

FkGravity::~FkGravity() {

}
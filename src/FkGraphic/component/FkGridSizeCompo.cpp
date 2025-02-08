/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: Alimin
* CREATE TIME: 2022-4-27 0:33:12
*/

#include "FkGridSizeCompo.h"

FK_IMPL_CLASS_TYPE(FkGridSizeCompo, FkComponent)

FkGridSizeCompo::FkGridSizeCompo(float x, float y) : FkFloatVec2Compo(x, y) {

}

FkGridSizeCompo::FkGridSizeCompo(const FkGridSizeCompo &o) : FkFloatVec2Compo(o) {

}

FkGridSizeCompo::~FkGridSizeCompo() {

}
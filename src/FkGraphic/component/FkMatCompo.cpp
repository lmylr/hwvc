/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: Alimin
* CREATE TIME: 2022-2-27 16:26:01
*/

#include "FkMatCompo.h"

FK_IMPL_CLASS_TYPE(FkMatCompo, FkAbsValueCompo)

FkMatCompo::FkMatCompo() : FkAbsValueCompo<FkMatrix>() {

}

FkMatCompo::FkMatCompo(const FkMatCompo &o) : FkAbsValueCompo<FkMatrix>(o) {

}

FkMatCompo::~FkMatCompo() {

}
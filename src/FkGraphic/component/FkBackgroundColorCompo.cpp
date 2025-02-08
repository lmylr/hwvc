/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: aliminabc@gmail.com

* CREATE TIME: 2024-06-05 23:14:26
*/

#include "FkBackgroundColorCompo.h"

FK_IMPL_CLASS_TYPE(FkBackgroundColorCompo, FkColorCompo)

FkBackgroundColorCompo::FkBackgroundColorCompo(const FkColor &color) : FkColorCompo(color) {

}

FkBackgroundColorCompo::FkBackgroundColorCompo(const FkBackgroundColorCompo &o) : FkColorCompo(o) {

}

FkBackgroundColorCompo::~FkBackgroundColorCompo() {

}
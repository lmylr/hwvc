/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: aliminabc@gmail.com

* CREATE TIME: 2024-06-08 23:52:45
*/

#include "FkColorAdjustCompo.h"

FK_IMPL_CLASS_TYPE(FkColorAdjustCompo, FkComponent)

FkColorAdjustCompo::FkColorAdjustCompo() : FkComponent() {

}

FkColorAdjustCompo::FkColorAdjustCompo(const FkColorAdjustCompo &o)
        : FkComponent(o), brightness(o.brightness), contrast(o.contrast), saturation(o.saturation) {

}

FkColorAdjustCompo::~FkColorAdjustCompo() {

}
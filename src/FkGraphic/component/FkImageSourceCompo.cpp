/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: aliminabc@gmail.com

* CREATE TIME: 2024-05-22 00:29:09
*/

#include "FkImageSourceCompo.h"

FK_IMPL_CLASS_TYPE(FkImageSourceCompo, FkAbsValueCompo)

FkImageSourceCompo::FkImageSourceCompo() : FkAbsValueCompo<FkAbsImageSource>() {

}

FkImageSourceCompo::FkImageSourceCompo(const FkImageSourceCompo &o)
        : FkAbsValueCompo<FkAbsImageSource>(o) {

}

FkImageSourceCompo::~FkImageSourceCompo() {

}

std::shared_ptr<FkComponent> FkImageSourceCompo::clone() {
    return std::make_shared<FkImageSourceCompo>(*this);
}
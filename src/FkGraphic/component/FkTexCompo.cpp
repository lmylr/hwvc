/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
* CREATE TIME: 2022-2-25 13:30:26
*/

#include "FkTexCompo.h"

FK_IMPL_CLASS_TYPE(FkTexCompo, FkComponent)

FkTexCompo::FkTexCompo(std::shared_ptr<FkGraphicTexture> &tex) : FkComponent(), tex(tex) {

}

FkTexCompo::FkTexCompo(const FkTexCompo &o) : FkComponent(o) {

}

FkTexCompo::~FkTexCompo() {

}
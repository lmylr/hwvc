/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: Alimin
* CREATE TIME: 2022-2-28 22:22:29
*/

#include "FkWindowProto.h"

FK_IMPL_CLASS_TYPE(FkWindowProto, FkProtocol)

FkWindowProto::FkWindowProto() : FkProtocol() {

}

FkWindowProto::FkWindowProto(const FkWindowProto &o) : FkProtocol(o), win(o.win) {

}

FkWindowProto::~FkWindowProto() {

}
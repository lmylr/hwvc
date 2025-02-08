/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
* CREATE TIME: 2022-2-25 13:14:50
*/

#include "FkNewTexProto.h"

FK_IMPL_CLASS_TYPE(FkNewTexProto, FkProtocol)

FkNewTexProto::FkNewTexProto() : FkProtocol() {

}

FkNewTexProto::FkNewTexProto(const FkNewTexProto &o) : FkProtocol(o), texEntity(o.texEntity) {

}

FkNewTexProto::~FkNewTexProto() {

}
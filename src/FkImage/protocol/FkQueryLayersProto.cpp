/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
* CREATE TIME: 2022-3-12 9:59:53
*/

#include "FkQueryLayersProto.h"

FK_IMPL_CLASS_TYPE(FkQueryLayersProto, FkProtocol)

FkQueryLayersProto::FkQueryLayersProto() : FkProtocol() {

}

FkQueryLayersProto::FkQueryLayersProto(const FkQueryLayersProto &o) : FkProtocol(o), layers(o.layers) {

}

FkQueryLayersProto::~FkQueryLayersProto() {

}
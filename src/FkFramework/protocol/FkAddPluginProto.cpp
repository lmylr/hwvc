/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: aliminabc@gmail.com

* CREATE TIME: 2024-06-07 23:44:28
*/

#include "FkAddPluginProto.h"

FK_IMPL_CLASS_TYPE(FkAddPluginProto, FkAbsValueProto)

FkAddPluginProto::FkAddPluginProto() : FkAbsValueProto<FkAbsPlugin>() {

}

FkAddPluginProto::FkAddPluginProto(const FkAddPluginProto &o) : FkAbsValueProto<FkAbsPlugin>(o) {

}

FkAddPluginProto::~FkAddPluginProto() {

}
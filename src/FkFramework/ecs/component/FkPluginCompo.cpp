/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: aliminabc@gmail.com

* CREATE TIME: 2024-06-07 23:43:35
*/

#include "FkPluginCompo.h"

FK_IMPL_CLASS_TYPE(FkPluginCompo, FkAbsValueCompo)

FkPluginCompo::FkPluginCompo() : FkAbsValueCompo<FkAbsPlugin>() {

}

FkPluginCompo::FkPluginCompo(const FkPluginCompo &o) : FkAbsValueCompo<FkAbsPlugin>(o) {

}

FkPluginCompo::~FkPluginCompo() {

}
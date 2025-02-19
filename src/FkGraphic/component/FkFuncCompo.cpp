/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: Alimin
* CREATE TIME: 2022-2-26 22:05:26
*/

#include "FkFuncCompo.h"

FK_IMPL_CLASS_TYPE(FkFuncCompo, FkComponent)

FkFuncCompo::FkFuncCompo(std::function<void()> func) : FkComponent(), func(func) {

}

FkFuncCompo::FkFuncCompo(const FkFuncCompo &o) : FkComponent(o), func(o.func) {

}

FkFuncCompo::~FkFuncCompo() {
    func = nullptr;
}
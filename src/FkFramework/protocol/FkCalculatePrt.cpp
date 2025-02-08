/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#include "FkCalculatePrt.h"

FK_IMPL_CLASS_TYPE(FkCalculatePrt, FkProtocol)

FkCalculatePrt::FkCalculatePrt() : FkProtocol() {

}

FkCalculatePrt::FkCalculatePrt(const FkCalculatePrt &o) : FkProtocol(o), number(o.number) {

}

FkCalculatePrt::~FkCalculatePrt() {

}
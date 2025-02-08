/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#include "FkRenderProto.h"

FK_IMPL_CLASS_TYPE(FkRenderProto, FkProtocol)

FkRenderProto::FkRenderProto(int64_t reqId) : FkProtocol(), reqId(reqId) {

}

FkRenderProto::FkRenderProto(const FkRenderProto &o) : FkProtocol(o), env(o.env), reqId(o.reqId),
                                                       materials(o.materials), device(o.device) {

}

FkRenderProto::~FkRenderProto() {

}
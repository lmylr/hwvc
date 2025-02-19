/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
* CREATE TIME: 2022-5-6 13:07:48
*/

#include "FkDrawPathProto.h"

FK_IMPL_CLASS_TYPE(FkDrawPathProto, FkProtocol)

FkDrawPathProto::FkDrawPathProto(FkID layerId, FkDoubleVec2 &point)
        : FkProtocol(), layerId(layerId), point(point), isFinish(false) {

}

FkDrawPathProto::FkDrawPathProto(const FkDrawPathProto &o)
        : FkProtocol(o), layerId(o.layerId), point(o.point), isFinish(o.isFinish) {

}

FkDrawPathProto::~FkDrawPathProto() {

}
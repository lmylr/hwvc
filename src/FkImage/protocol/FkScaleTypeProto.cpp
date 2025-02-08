/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
* CREATE TIME: 2022-4-29 13:00:31
*/

#include "FkScaleTypeProto.h"

FK_IMPL_CLASS_TYPE(FkScaleTypeProto, FkWinSizeProto)

FkScaleTypeProto::FkScaleTypeProto()
        : FkWinSizeProto(), layerId(FK_ID_NONE), scaleType(kScaleType::CENTER_MATRIX) {

}

FkScaleTypeProto::FkScaleTypeProto(FkID layerId, kScaleType scaleType)
        : FkWinSizeProto(), layerId(layerId), scaleType(scaleType) {

}

FkScaleTypeProto::FkScaleTypeProto(const FkScaleTypeProto &o)
        : FkWinSizeProto(o), layerId(o.layerId), scaleType(o.scaleType) {

}

FkScaleTypeProto::~FkScaleTypeProto() {

}
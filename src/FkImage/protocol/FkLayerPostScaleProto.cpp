/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#include "FkLayerPostScaleProto.h"

FK_IMPL_CLASS_TYPE(FkLayerPostScaleProto, FkFloatVec3Proto)

FkLayerPostScaleProto::FkLayerPostScaleProto()
        : FkFloatVec3Proto(), layer(FK_ID_NONE) {

}

FkLayerPostScaleProto::FkLayerPostScaleProto(const FkLayerPostScaleProto &o)
        : FkFloatVec3Proto(o), layer(o.layer) {

}

FkLayerPostScaleProto::~FkLayerPostScaleProto() {

}
/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: aliminabc@gmail.com

* CREATE TIME: 2024-05-22 00:19:32
*/

#include "FkLayerSetSourceProto.h"

FK_IMPL_CLASS_TYPE(FkLayerSetSourceProto, FkGraphicUpdateLayerPrt)

FkLayerSetSourceProto::FkLayerSetSourceProto(FkID layerId) : FkGraphicUpdateLayerPrt(), layerId(layerId) {

}

FkLayerSetSourceProto::FkLayerSetSourceProto(const FkLayerSetSourceProto &o)
        : FkGraphicUpdateLayerPrt(o), layerId(o.layerId), source(o.source) {

}

FkLayerSetSourceProto::~FkLayerSetSourceProto() {
    layerId = FK_ID_NONE;
    source = nullptr;
}
/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns)

* CREATE TIME: 2024-03-09 16:19:26
*/

#include "FkCropLayerProto.h"

FK_IMPL_CLASS_TYPE(FkCropLayerProto, FkProtocol)

FkCropLayerProto::FkCropLayerProto(const FkID layerId, const FkIntRect &rect)
        : FkProtocol(), layerId(layerId), rect(rect) {

}

FkCropLayerProto::FkCropLayerProto(const FkCropLayerProto &o)
        : FkProtocol(o), layerId(o.layerId), rect(o.rect) {

}

FkCropLayerProto::~FkCropLayerProto() {

}
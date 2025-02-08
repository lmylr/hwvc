/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns)

* CREATE TIME: 2024-06-05 23:59:15
*/

#include "FkLayerSetBackgroundColorProto.h"

FK_IMPL_CLASS_TYPE(FkLayerSetBackgroundColorProto, FkAbsValueProto)

FkLayerSetBackgroundColorProto::FkLayerSetBackgroundColorProto(FkID layerId) : FkAbsValueProto<FkColor>(), layerId(layerId) {

}

FkLayerSetBackgroundColorProto::FkLayerSetBackgroundColorProto(const FkLayerSetBackgroundColorProto &o) : FkAbsValueProto<FkColor>(o), layerId(o.layerId) {

}

FkLayerSetBackgroundColorProto::~FkLayerSetBackgroundColorProto() {

}
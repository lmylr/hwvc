/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: aliminabc@gmail.com

* CREATE TIME: 2024-06-09 23:43:43
*/

#include "FkLayerSetVisibilityProto.h"

FK_IMPL_CLASS_TYPE(FkLayerSetVisibilityProto, FkProtocol)

FkLayerSetVisibilityProto::FkLayerSetVisibilityProto() : FkProtocol() {

}

FkLayerSetVisibilityProto::FkLayerSetVisibilityProto(const FkLayerSetVisibilityProto &o)
        : FkProtocol(o), layerId(o.layerId), visibility(o.visibility) {

}

FkLayerSetVisibilityProto::~FkLayerSetVisibilityProto() {

}
/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: aliminabc@gmail.com

* CREATE TIME: 2024-06-05 23:59:15
*/

#ifndef FK_IMAGE_FKLAYERSETBACKGROUNDCOLORPROTO_H
#define FK_IMAGE_FKLAYERSETBACKGROUNDCOLORPROTO_H

#include "FkAbsValueProto.h"
#include "FkColor.h"

FK_SUPER_TEMPLATE_CLASS_IMPL(FkLayerSetBackgroundColorProto, FkAbsValueProto)<FkColor> {
FK_DEF_CLASS_TYPE_FUNC(FkLayerSetBackgroundColorProto)

public:
    FkLayerSetBackgroundColorProto(FkID layerId);

    FkLayerSetBackgroundColorProto(const FkLayerSetBackgroundColorProto &o);

    virtual ~FkLayerSetBackgroundColorProto();

public:
    FkID layerId = FK_ID_NONE;
};

#endif //FK_IMAGE_FKLAYERSETBACKGROUNDCOLORPROTO_H
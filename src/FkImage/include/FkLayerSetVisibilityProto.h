/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns)

* CREATE TIME: 2024-06-09 23:43:43
*/

#ifndef FK_IMAGE_FKLAYERSETVISIBILITYPROTO_H
#define FK_IMAGE_FKLAYERSETVISIBILITYPROTO_H

#include "FkProtocol.h"

FK_SUPER_CLASS(FkLayerSetVisibilityProto, FkProtocol) {
FK_DEF_CLASS_TYPE_FUNC(FkLayerSetVisibilityProto)

public:
    FkLayerSetVisibilityProto();

    FkLayerSetVisibilityProto(const FkLayerSetVisibilityProto &o);

    virtual ~FkLayerSetVisibilityProto();

public:
    FkID layerId = FK_ID_NONE;
    kVisibility visibility = kVisibility::VISIBLE;
};

#endif //FK_IMAGE_FKLAYERSETVISIBILITYPROTO_H
/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: Alimin
* CREATE TIME: 2022-4-19 23:37:02
*/

#ifndef FK_IMAGE_FKLAYERPROTO_H
#define FK_IMAGE_FKLAYERPROTO_H

#include "FkProtocol.h"
#include "FkGraphicLayer.h"

FK_SUPER_CLASS(FkLayerProto, FkProtocol) {
FK_DEF_CLASS_TYPE_FUNC(FkLayerProto)

public:
    FkLayerProto();

    FkLayerProto(const FkLayerProto &o);

    virtual ~FkLayerProto();
public:
    FkID layerId = FK_ID_NONE;
    std::shared_ptr<FkGraphicLayer> layer = nullptr;
};

#endif //FK_IMAGE_FKLAYERPROTO_H
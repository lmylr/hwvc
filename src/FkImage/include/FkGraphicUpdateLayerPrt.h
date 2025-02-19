/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#ifndef FK_GRAPHIC_FKGRAPHICUPDATELAYERPRT_H
#define FK_GRAPHIC_FKGRAPHICUPDATELAYERPRT_H

#include "FkWinSizeProto.h"
#include "FkGraphicLayer.h"

FK_SUPER_CLASS(FkGraphicUpdateLayerPrt, FkWinSizeProto) {
FK_DEF_CLASS_TYPE_FUNC(FkGraphicUpdateLayerPrt)

public:
    FkGraphicUpdateLayerPrt();

    FkGraphicUpdateLayerPrt(const FkGraphicUpdateLayerPrt &o);

    virtual ~FkGraphicUpdateLayerPrt();

public:
    std::shared_ptr<FkGraphicLayer> layer = nullptr;
    kScaleType scaleType;
};


#endif //FK_GRAPHIC_FKGRAPHICUPDATELAYERPRT_H

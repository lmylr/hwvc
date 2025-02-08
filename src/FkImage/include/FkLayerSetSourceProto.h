/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns)

* CREATE TIME: 2024-05-22 00:19:32
*/

#ifndef FK_IMAGE_FKLAYERSETSOURCEPROTO_H
#define FK_IMAGE_FKLAYERSETSOURCEPROTO_H

#include "FkGraphicUpdateLayerPrt.h"
#include "FkAbsImageSource.h"

FK_SUPER_CLASS(FkLayerSetSourceProto, FkGraphicUpdateLayerPrt) {
FK_DEF_CLASS_TYPE_FUNC(FkLayerSetSourceProto)

public:
    FkLayerSetSourceProto(FkID layerId);

    FkLayerSetSourceProto(const FkLayerSetSourceProto &o);

    virtual ~FkLayerSetSourceProto();

public:
    FkID layerId = FK_ID_NONE;
    std::string filePath = "";
    std::shared_ptr<FkAbsImageSource> source = nullptr;
};

#endif //FK_IMAGE_FKLAYERSETSOURCEPROTO_H
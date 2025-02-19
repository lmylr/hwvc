/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
* CREATE TIME: 2022-4-29 13:00:31
*/

#ifndef FK_IMAGE_FKSCALETYPEPROTO_H
#define FK_IMAGE_FKSCALETYPEPROTO_H

#include "FkWinSizeProto.h"

FK_SUPER_CLASS(FkScaleTypeProto, FkWinSizeProto) {
FK_DEF_CLASS_TYPE_FUNC(FkScaleTypeProto)

public:
    FkScaleTypeProto();

    FkScaleTypeProto(FkID layerId, kScaleType scaleType);

    FkScaleTypeProto(const FkScaleTypeProto &o);

    virtual ~FkScaleTypeProto();

public:
    FkID layerId = FK_ID_NONE;
    kScaleType scaleType;
};

#endif //FK_IMAGE_FKSCALETYPEPROTO_H
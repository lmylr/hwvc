/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#ifndef FK_GRAPHIC_FKLAYERROTATEPROTO_H
#define FK_GRAPHIC_FKLAYERROTATEPROTO_H

#include "FkRationalProto.h"

FK_SUPER_CLASS(FkLayerPostRotateProto, FkRationalProto) {
FK_DEF_CLASS_TYPE_FUNC(FkLayerPostRotateProto)

public:
    FkLayerPostRotateProto();

    FkLayerPostRotateProto(const FkLayerPostRotateProto &o);

    virtual ~FkLayerPostRotateProto();

public:
    FkID layer = FK_ID_NONE;
};

#endif //FK_GRAPHIC_FKLAYERROTATEPROTO_H
/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: Alimin
* CREATE TIME: 2022-4-16 21:06:37
*/

#ifndef FK_IMAGE_FKREMOVELAYERPROTO_H
#define FK_IMAGE_FKREMOVELAYERPROTO_H

#include "FkLayerIdProto.h"

FK_SUPER_CLASS(FkRemoveLayerProto, FkLayerIdProto) {
FK_DEF_CLASS_TYPE_FUNC(FkRemoveLayerProto)

public:
    FkRemoveLayerProto();

    FkRemoveLayerProto(FkID layerId);

    FkRemoveLayerProto(const FkRemoveLayerProto &o);

    virtual ~FkRemoveLayerProto();
};

#endif //FK_IMAGE_FKREMOVELAYERPROTO_H
/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
* CREATE TIME: 2025-02-09 11:53:21
*/

#ifndef FK_CODEC_FKABSCODEC_H
#define FK_CODEC_FKABSCODEC_H

#include "FkObject.h"

FK_SUPER_CLASS(FkAbsCodec, FkObject) {
FK_DEF_CLASS_TYPE_FUNC(FkAbsCodec)

public:
    FkAbsCodec();

    FkAbsCodec(const FkAbsCodec &o);

    virtual ~FkAbsCodec();
};

#endif //FK_CODEC_FKABSCODEC_H
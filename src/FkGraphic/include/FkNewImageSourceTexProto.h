/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns)

* CREATE TIME: 2024-05-24 13:14:50
*/

#ifndef FK_GRAPHIC_FKNEWIMAGESOURCETEXPROTO_H
#define FK_GRAPHIC_FKNEWIMAGESOURCETEXPROTO_H

#include "FkNewTexProto.h"

FK_SUPER_CLASS(FkNewImageSourceTexProto, FkNewTexProto) {
FK_DEF_CLASS_TYPE_FUNC(FkNewImageSourceTexProto)

public:
    FkNewImageSourceTexProto();

    FkNewImageSourceTexProto(const FkNewImageSourceTexProto &o);

    virtual ~FkNewImageSourceTexProto();
};

#endif //FK_GRAPHIC_FKNEWIMAGESOURCETEXPROTO_H
/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: Alimin
* CREATE TIME: 2022-2-27 14:40:57
*/

#ifndef FK_GRAPHIC_FKCOORDINATECOMPO_H
#define FK_GRAPHIC_FKCOORDINATECOMPO_H

#include "FkVertexCompo.h"
#include "FkRect.h"

FK_SUPER_CLASS(FkCoordinateCompo, FkVertexCompo) {
FK_DEF_CLASS_TYPE_FUNC(FkCoordinateCompo)

public:
    FkCoordinateCompo();

    FkCoordinateCompo(FkFloatRect rectF);

    FkCoordinateCompo(const FkCoordinateCompo &o);

    virtual ~FkCoordinateCompo();
};

#endif //FK_GRAPHIC_FKCOORDINATECOMPO_H
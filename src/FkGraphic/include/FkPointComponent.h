/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#ifndef FK_GRAPHIC_FKPOINTCOMPONENT_H
#define FK_GRAPHIC_FKPOINTCOMPONENT_H

#include "FkGraphicComponent.h"
#include "FkIntVec2.h"
#include "FkColor.h"

FK_SUPER_CLASS(FkPointComponent, FkGraphicComponent) {
FK_DEF_CLASS_TYPE_FUNC(FkPointComponent)

public:
    FkPointComponent();

    FkPointComponent(const FkPointComponent &o);

    virtual ~FkPointComponent();

public:
    FkIntVec2 value;
    FkColor color;
};

#endif //FK_GRAPHIC_FKPOINTCOMPONENT_H
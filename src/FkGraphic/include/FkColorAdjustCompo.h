/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns)

* CREATE TIME: 2024-06-08 23:52:45
*/

#ifndef FK_GRAPHIC_FKCOLORADJUSTCOMPO_H
#define FK_GRAPHIC_FKCOLORADJUSTCOMPO_H

#include "FkComponent.h"

FK_SUPER_CLASS(FkColorAdjustCompo, FkComponent) {
FK_DEF_CLASS_TYPE_FUNC(FkColorAdjustCompo)

public:
    FkColorAdjustCompo();

    FkColorAdjustCompo(const FkColorAdjustCompo &o);

    virtual ~FkColorAdjustCompo();

public:
    float brightness = 0.0f;//[-1, 1]
    float contrast = 1.0f;//[0, 2]
    float saturation = 1.0f;//[0 2]
};

#endif //FK_GRAPHIC_FKCOLORADJUSTCOMPO_H
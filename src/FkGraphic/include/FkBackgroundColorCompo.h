/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns)

* CREATE TIME: 2024-06-05 23:14:26
*/

#ifndef FK_GRAPHIC_FKBACKGROUNDCOLORCOMPO_H
#define FK_GRAPHIC_FKBACKGROUNDCOLORCOMPO_H

#include "FkColorCompo.h"

FK_SUPER_CLASS(FkBackgroundColorCompo, FkColorCompo) {
FK_DEF_CLASS_TYPE_FUNC(FkBackgroundColorCompo)

public:
    FkBackgroundColorCompo(const FkColor &color);

    FkBackgroundColorCompo(const FkBackgroundColorCompo &o);

    virtual ~FkBackgroundColorCompo();
};

#endif //FK_GRAPHIC_FKBACKGROUNDCOLORCOMPO_H
/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns)

* CREATE TIME: 2024-05-25 15:25:49
*/

#ifndef FK_GRAPHIC_FKTRANSMATCOMPO_H
#define FK_GRAPHIC_FKTRANSMATCOMPO_H

#include "FkMatCompo.h"

FK_SUPER_CLASS(FkTransMatCompo, FkMatCompo) {
FK_DEF_CLASS_TYPE_FUNC(FkTransMatCompo)

public:
    FkTransMatCompo();

    FkTransMatCompo(const FkTransMatCompo &o);

    virtual ~FkTransMatCompo();
};

#endif //FK_GRAPHIC_FKTRANSMATCOMPO_H
/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: Alimin
* CREATE TIME: 2022-2-27 16:26:01
*/

#ifndef FK_GRAPHIC_FKMATCOMPO_H
#define FK_GRAPHIC_FKMATCOMPO_H

#include "FkAbsValueCompo.h"
#include "FkMatrix.h"

FK_SUPER_TEMPLATE_CLASS_IMPL(FkMatCompo, FkAbsValueCompo)<FkMatrix> {
FK_DEF_CLASS_TYPE_FUNC(FkMatCompo)

public:
    FkMatCompo();

    FkMatCompo(const FkMatCompo &o);

    virtual ~FkMatCompo();

};

#endif //FK_GRAPHIC_FKMATCOMPO_H
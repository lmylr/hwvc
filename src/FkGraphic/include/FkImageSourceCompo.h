/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: aliminabc@gmail.com

* CREATE TIME: 2024-05-22 00:29:09
*/

#ifndef FK_GRAPHIC_FKIMAGESOURCECOMPO_H
#define FK_GRAPHIC_FKIMAGESOURCECOMPO_H

#include "FkAbsValueCompo.h"
#include "FkAbsImageSource.h"

FK_SUPER_TEMPLATE_CLASS_IMPL(FkImageSourceCompo, FkAbsValueCompo)<FkAbsImageSource> {
FK_DEF_CLASS_TYPE_FUNC(FkImageSourceCompo)

public:
    FkImageSourceCompo();

    FkImageSourceCompo(const FkImageSourceCompo &o);

    virtual ~FkImageSourceCompo();

    virtual std::shared_ptr<FkComponent> clone() override;

};

#endif //FK_GRAPHIC_FKIMAGESOURCECOMPO_H
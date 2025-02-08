/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: aliminabc@gmail.com

* CREATE TIME: 2024-06-07 23:43:35
*/

#ifndef FK_FRAMEWORK_FKPLUGINCOMPO_H
#define FK_FRAMEWORK_FKPLUGINCOMPO_H

#include "FkAbsValueCompo.h"
#include "FkAbsPlugin.h"

FK_SUPER_TEMPLATE_CLASS_IMPL(FkPluginCompo, FkAbsValueCompo)<FkAbsPlugin> {
FK_DEF_CLASS_TYPE_FUNC(FkPluginCompo)
public:
    FkPluginCompo();

    FkPluginCompo(const FkPluginCompo &o);

    virtual ~FkPluginCompo();
};

#endif //FK_FRAMEWORK_FKPLUGINCOMPO_H
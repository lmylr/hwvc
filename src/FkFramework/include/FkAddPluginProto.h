/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: aliminabc@gmail.com

* CREATE TIME: 2024-06-07 23:44:28
*/

#ifndef FK_FRAMEWORK_FKADDPLUGINPROTO_H
#define FK_FRAMEWORK_FKADDPLUGINPROTO_H

#include "FkAbsValueProto.h"
#include "FkAbsPlugin.h"

FK_SUPER_TEMPLATE_CLASS_IMPL(FkAddPluginProto, FkAbsValueProto)<FkAbsPlugin> {
FK_DEF_CLASS_TYPE_FUNC(FkAddPluginProto)
public:
    FkAddPluginProto();

    FkAddPluginProto(const FkAddPluginProto &o);

    virtual ~FkAddPluginProto();

public:
    FkID layerId = FK_ID_NONE;
};

#endif //FK_FRAMEWORK_FKADDPLUGINPROTO_H
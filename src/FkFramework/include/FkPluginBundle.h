/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: aliminabc@gmail.com

* CREATE TIME: 2024-06-07 23:54:12
*/

#ifndef FK_FRAMEWORK_FKPLUGINBUNDLE_H
#define FK_FRAMEWORK_FKPLUGINBUNDLE_H

#include "FkObject.h"
#include "FkPluginRequirements.h"
#include <any>
#include <unordered_map>

FK_SUPER_CLASS(FkPluginBundle, FkObject) {
FK_DEF_CLASS_TYPE_FUNC(FkPluginBundle)

public:
    FkPluginBundle();

    FkPluginBundle(const FkPluginBundle &o);

    virtual ~FkPluginBundle();

    void add(FkPluginRequirements::Type type, std::any value);

    std::any get(FkPluginRequirements::Type type);

    bool contains(FkPluginRequirements::Type type);

    size_t size();

private:
    std::unordered_map<FkPluginRequirements::Type, std::any> _map;
};

#endif //FK_FRAMEWORK_FKPLUGINBUNDLE_H
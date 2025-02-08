/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns)

* CREATE TIME: 2024-06-07 23:53:19
*/

#include "FkPluginRequirements.h"

FK_IMPL_CLASS_TYPE(FkPluginRequirements, FkObject)

FkPluginRequirements::FkPluginRequirements() : FkObject() {

}

FkPluginRequirements::FkPluginRequirements(const FkPluginRequirements &o) : FkObject(o) {
    _map = o._map;
}

FkPluginRequirements::~FkPluginRequirements() {
    _map.clear();
}

void FkPluginRequirements::add(Type type) {
    add(type, nullptr);
}

void FkPluginRequirements::add(Type type, const std::any &any) {
    _map[type] = any;
}

bool FkPluginRequirements::contains(Type type) {
    return _map.find(type) != _map.end();
}

void FkPluginRequirements::forEach(ForEachFunc func) {
    for (auto &itr: _map) {
        func(itr.first, itr.second);
    }
}
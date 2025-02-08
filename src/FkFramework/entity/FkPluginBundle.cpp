/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: aliminabc@gmail.com

* CREATE TIME: 2024-06-07 23:54:12
*/

#include "FkPluginBundle.h"

FK_IMPL_CLASS_TYPE(FkPluginBundle, FkObject)

FkPluginBundle::FkPluginBundle() : FkObject() {

}

FkPluginBundle::FkPluginBundle(const FkPluginBundle &o) : FkObject(o) {
    _map = o._map;
}

FkPluginBundle::~FkPluginBundle() {

}

void FkPluginBundle::add(FkPluginRequirements::Type type, std::any value) {
    _map[type] = value;
}

std::any FkPluginBundle::get(FkPluginRequirements::Type type) {
    auto itr = _map.find(type);
    if (_map.end() == itr) {
        return nullptr;
    }
    return itr->second;
}

bool FkPluginBundle::contains(FkPluginRequirements::Type type) {
    auto itr = _map.find(type);
    return _map.end() != itr;
}

size_t FkPluginBundle::size() {
    return _map.size();
}

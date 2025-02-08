/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: aliminabc@gmail.com

* CREATE TIME: 2024-06-07 23:42:07
*/

#include "FkAbsPlugin.h"

FK_IMPL_CLASS_TYPE(FkAbsPlugin, FkObject)

FkAbsPlugin::FkAbsPlugin() : FkObject() {

}

FkAbsPlugin::~FkAbsPlugin() {
    _params.clear();
}

FkResult FkAbsPlugin::updateParams(const std::unordered_map<std::string, FkValue> &params) {
    for (auto &itr: params) {
        _params[itr.first] = itr.second;
    }
    return FK_OK;
}

FkValue FkAbsPlugin::getParam(const std::string &key) {
    auto itr = _params.find(key);
    if (itr == _params.end()) {
        return FkValue(0);
    }
    return itr->second;
}
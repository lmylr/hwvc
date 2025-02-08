/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns)

* CREATE TIME: 2024/6/9.
*/

#include "FkAbsPlugin.h"
#include "FkColorAdjustPlugin.h"
#include "FkHistPlugin.h"
#include "FkInstanceHolder.h"
#include "FkValueMap.pb.h"
#include "FkJniDefinition.h"
#include <string>

using namespace com::alimin::fk::pb;

#define TAG "FkPluginFactory"

#ifdef __cplusplus
extern "C" {
#endif

void *FkPlugin_create(const char *name) {
    std::string str = name;
    std::shared_ptr<FkAbsPlugin> plugin = nullptr;
    if (str == "color_adjust") {
        plugin = std::make_shared<FkColorAdjustPlugin>();
    } else if (str == "image_histogram") {
        plugin = std::make_shared<FkHistPlugin>();
    }
    if (plugin) {
        return (void *) FkInstanceHolder::getInstance().put(plugin);
    } else {
        FkLogE(TAG, "[Fail] Can not create plugin by name=%s", name);
        return nullptr;
    }
}

int FkPlugin_updateParams(void *handle, const void *data, int size) {
    auto plugin = FkInstanceHolder::getInstance().find<std::shared_ptr<FkAbsPlugin>>((long) handle);
    if (plugin == nullptr) {
        return FK_FAIL;
    }
    auto map = FkValueMap();
    if (!map.ParseFromArray(data, size)) {
        return FK_INVALID_DATA;
    }
    std::unordered_map<std::string, FkValue> params;
    for (auto &itr : map.value()) {
        params.insert(std::make_pair(itr.first,
                                     FkValue(itr.second.int32val(), itr.second.int64val(),
                                             itr.second.floatval(), itr.second.doubleval(),
                                             itr.second.strval())));
    }
    return plugin->updateParams(params);
}

Array FkPlugin_getParam(void *handle, const char *key) {
    auto plugin = FkInstanceHolder::getInstance().find<std::shared_ptr<FkAbsPlugin>>((long) handle);
    if (plugin == nullptr) {
        FkLogW(TAG, "[Fail] Get plugin instance(%p)", handle);
        return {};
    }
    auto value = plugin->getParam(key);
    FkPbValue pbValue;
    pbValue.set_int32val(value.getInt32());
    pbValue.set_int64val(value.getInt64());
    pbValue.set_floatval(value.getFloat());
    pbValue.set_doubleval(value.getDouble());
    pbValue.set_strval(value.getString());

    Array array;
    array.len = pbValue.ByteSizeLong();
    array.data = new uint8_t[array.len];
    if (!pbValue.SerializeToArray(array.data, array.len)) {
        array.len = 0;
        delete[] array.data;
        FkLogW(TAG, "[Fail] Get value by key=%s", key);
        return {};
    }
    return array;
}

#ifdef __cplusplus
}
#endif

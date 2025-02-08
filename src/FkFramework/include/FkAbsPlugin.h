/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns)

* CREATE TIME: 2024-06-07 23:42:07
*/

#ifndef FK_FRAMEWORK_FKABSPLUGIN_H
#define FK_FRAMEWORK_FKABSPLUGIN_H

#include "FkObject.h"
#include "FkValue.h"
#include "FkPluginBundle.h"
#include "FkPluginRequirements.h"
#include <unordered_map>

FK_SUPER_CLASS(FkAbsPlugin, FkObject) {
FK_DEF_CLASS_TYPE_FUNC(FkAbsPlugin)

public:
    FkAbsPlugin();

    FkAbsPlugin(const FkAbsPlugin &o) = delete;

    virtual ~FkAbsPlugin();

    virtual FkResult onCreate() = 0;

    virtual FkResult onDestroy() = 0;

    virtual FkPluginRequirements describeRequirements() = 0;

    virtual FkResult onPreProcess() = 0;

    virtual FkResult onProcess(const std::shared_ptr<FkPluginBundle> &bundle) = 0;

    virtual FkResult onPostProcess() = 0;

    FkResult updateParams(const std::unordered_map<std::string, FkValue> &params);

    virtual FkValue getParam(const std::string &key);

private:
    std::unordered_map<std::string, FkValue> _params;
};

#endif //FK_FRAMEWORK_FKABSPLUGIN_H
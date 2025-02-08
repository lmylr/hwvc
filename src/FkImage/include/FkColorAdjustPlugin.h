/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: aliminabc@gmail.com

* CREATE TIME: 2024-06-08 00:07:26
*/

#ifndef FK_IMAGE_FKSATURATIONPLUGIN_H
#define FK_IMAGE_FKSATURATIONPLUGIN_H

#include "FkAbsPlugin.h"
#include "FkGraphicProgram.h"

FK_SUPER_CLASS(FkColorAdjustPlugin, FkAbsPlugin) {
FK_DEF_CLASS_TYPE_FUNC(FkColorAdjustPlugin)

public:
    FkColorAdjustPlugin();

    FkColorAdjustPlugin(const FkColorAdjustPlugin &o) = delete;

    virtual ~FkColorAdjustPlugin();

    virtual FkResult onCreate() override;

    virtual FkResult onDestroy() override;

    virtual FkPluginRequirements describeRequirements() override;

    virtual FkResult onPreProcess() override;

    virtual FkResult onProcess(const std::shared_ptr<FkPluginBundle> &bundle) override;

    virtual FkResult onPostProcess() override;

private:
    std::shared_ptr<FkGraphicProgram> program = nullptr;
};

#endif //FK_IMAGE_FKSATURATIONPLUGIN_H
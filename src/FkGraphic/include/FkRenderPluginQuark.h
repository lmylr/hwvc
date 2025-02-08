/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: aliminabc@gmail.com

* CREATE TIME: 2024-06-08 10:44:16
*/

#ifndef FK_GRAPHIC_FKRENDERPLUGINQUARK_H
#define FK_GRAPHIC_FKRENDERPLUGINQUARK_H

#include "FkQuark.h"
#include "FkAbsPlugin.h"
#include "FkRenderProto.h"
#include <unordered_map>

FK_SUPER_CLASS(FkRenderPluginQuark, FkQuark) {
FK_DEF_CLASS_TYPE_FUNC(FkRenderPluginQuark)

public:
    FkRenderPluginQuark();

    FkRenderPluginQuark(const FkRenderPluginQuark &o) = delete;

    virtual ~FkRenderPluginQuark();

    virtual FkResult onDestroy() override;

protected:
    virtual void describeProtocols(std::shared_ptr<FkPortDesc> desc) override;

private:
    FkResult _onAdd(const std::shared_ptr<FkProtocol> &p);

    FkResult _onRemove(const std::shared_ptr<FkProtocol> &p);

    FkResult _onRender(const std::shared_ptr<FkProtocol> &p);

    FkResult _onPreProcess(const std::shared_ptr<FkAbsPlugin> &plugin);

    FkResult _onProcess(const std::shared_ptr<FkAbsPlugin> &plugin,
                        const std::shared_ptr<FkPluginBundle> &bundle,
                        int64_t reqId);

    FkResult _onPostProcess(const std::shared_ptr<FkAbsPlugin> &plugin);

    FkResult _addMaterials(const std::shared_ptr<FkPluginBundle> &bundle,
                           const std::shared_ptr<FkRenderProto> &proto,
                           FkPluginRequirements::Type type,
                           const std::any &any);

private:
    std::unordered_map<FkID, std::shared_ptr<FkAbsPlugin>> _map;
};

#endif //FK_GRAPHIC_FKRENDERPLUGINQUARK_H
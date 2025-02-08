/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns)

* CREATE TIME: 2024-06-08 10:44:16
*/

#include "FkRenderPluginQuark.h"
#include "FkRenderProto.h"
#include "FkTexEntity.h"
#include "FkRmMaterialProto.h"
#include "FkVboCompo.h"
#include "FkMatCompo.h"
#include "FkImageSourceCompo.h"
#include "FkTransMatCompo.h"

FK_IMPL_CLASS_TYPE(FkRenderPluginQuark, FkQuark)

FkRenderPluginQuark::FkRenderPluginQuark() : FkQuark() {

}

FkRenderPluginQuark::~FkRenderPluginQuark() {

}

void FkRenderPluginQuark::describeProtocols(std::shared_ptr<FkPortDesc> desc) {
    FK_PORT_DESC_QUICK_ADD(desc, FkRenderProto, FkRenderPluginQuark::_onRender);
    FK_PORT_DESC_QUICK_ADD(desc, FkRmMaterialProto, FkRenderPluginQuark::_onRemove);
}

FkResult FkRenderPluginQuark::onDestroy() {
    for (auto &itr: _map) {
        if (itr.second->describeRequirements().contains(FkPluginRequirements::Type::THREAD_GL)) {
            itr.second->onDestroy();
        }
    }
    _map.clear();
    return FK_OK;
}

FkResult FkRenderPluginQuark::_onAdd(const std::shared_ptr<FkProtocol> &p) {
    return FK_OK;
}

FkResult FkRenderPluginQuark::_onRemove(const std::shared_ptr<FkProtocol> &p) {
    FK_CAST_NULLABLE_PTR_RETURN_INT(proto, FkRmMaterialProto, p);
    if (proto->material == nullptr) {
        return FK_NPE;
    }
    auto itr = _map.find(proto->material->id());
    if (itr != _map.end() && itr->second->describeRequirements().contains(FkPluginRequirements::Type::THREAD_GL)) {
        itr->second->onDestroy();
        _map.erase(itr);
    }
    return FK_OK;
}

FkResult FkRenderPluginQuark::_onRender(const std::shared_ptr<FkProtocol> &p) {
    FK_CAST_NULLABLE_PTR_RETURN_INT(proto, FkRenderProto, p);
    if (!FK_INSTANCE_OF(proto->device, FkTexDeviceEntity)) {
        return FK_SKIP;
    }
    FK_CAST_NULLABLE_PTR_RETURN_INT(materials, FkTexEntity, proto->materials);
    auto pluginCompo = materials->getPlugin();
    if (pluginCompo == nullptr || pluginCompo->value == nullptr) {
        FkLogD(FK_DEF_TAG, "Not support for multi-texture frame buffer object.");
        return FK_SKIP;
    }
    auto plugin = pluginCompo->value;
    if (plugin->describeRequirements().contains(FkPluginRequirements::Type::THREAD_GL)
        && _map.find(materials->getMaterial()->id()) == _map.end()) {
        _map.emplace(std::make_pair(materials->getMaterial()->id(), plugin));
        plugin->onCreate();
    }
    FkResult ret = _onPreProcess(pluginCompo->value);
    if (ret != FK_OK) {
        return ret;
    }
    auto bundle = std::make_shared<FkPluginBundle>();
    pluginCompo->value->describeRequirements().forEach(
            [=](FkPluginRequirements::Type type, const std::any &any) {
                _addMaterials(bundle, proto, type, any);
            });
    ret = _onProcess(pluginCompo->value, bundle, proto->reqId);
    if (ret != FK_OK) {
        return ret;
    }
    ret = _onPostProcess(pluginCompo->value);
    if (ret != FK_OK) {
        return ret;
    }
    return FK_DONE;
}

FkResult FkRenderPluginQuark::_onPreProcess(const std::shared_ptr<FkAbsPlugin> &plugin) {
    return plugin->onPreProcess();
}

FkResult FkRenderPluginQuark::_onProcess(const std::shared_ptr<FkAbsPlugin> &plugin,
                                         const std::shared_ptr<FkPluginBundle> &bundle,
                                         int64_t reqId) {
    auto srcTexArray = std::any_cast<std::shared_ptr<FkTexArrayCompo>>(bundle->get(FkPluginRequirements::Type::GL_INPUT));
    std::shared_ptr<FkAbsImageSource> imageSource = nullptr;
    if (bundle->contains(FkPluginRequirements::Type::GL_INPUT_IMAGE)) {
        imageSource = std::any_cast<std::shared_ptr<FkAbsImageSource>>(bundle->get(FkPluginRequirements::Type::GL_INPUT_IMAGE));
    }
    std::shared_ptr<FkTransMatCompo> transMatCompo = nullptr;
    if (imageSource) {
        transMatCompo = std::make_shared<FkTransMatCompo>();
        transMatCompo->value = imageSource->getTransformMatrix();
        if (transMatCompo->value->isZero()) {
            imageSource->onRender(srcTexArray->textures[0]->tex, reqId, "");
            return FK_SKIP;
        }
    }
    bundle->add(FkPluginRequirements::Type::RENDER_REQ_ID, reqId);
    bundle->add(FkPluginRequirements::Type::GL_TRANS_MATRIX, transMatCompo);
    auto ret = plugin->onProcess(bundle);
    if (imageSource) {
        imageSource->onRender(srcTexArray->textures[0]->tex, reqId, "");
    }
    return ret;
}

FkResult FkRenderPluginQuark::_onPostProcess(const std::shared_ptr<FkAbsPlugin> &plugin) {
    return plugin->onPostProcess();
}

FkResult FkRenderPluginQuark::_addMaterials(const std::shared_ptr<FkPluginBundle> &bundle,
                                            const std::shared_ptr<FkRenderProto> &proto,
                                            FkPluginRequirements::Type type,
                                            const std::any &any) {
    FK_CAST_NULLABLE_PTR_RETURN_INT(device, FkTexDeviceEntity, proto->device);
    FK_CAST_NULLABLE_PTR_RETURN_INT(materials, FkTexEntity, proto->materials);
    switch (type) {
        case FkPluginRequirements::Type::GL_FBO:
            bundle->add(type, materials->fbo());
            break;
        case FkPluginRequirements::Type::GL_INPUT:
            bundle->add(type, materials->texArray());
            break;
        case FkPluginRequirements::Type::GL_INPUT_IMAGE: {
            auto imageSourceCompo = FK_FIND_COMPO(proto->materials, FkImageSourceCompo);
            if (imageSourceCompo) {
                bundle->add(type, imageSourceCompo->value);
            }
            break;
        }
        case FkPluginRequirements::Type::GL_VBO: {
            auto vboCompo = FK_FIND_COMPO(proto->materials, FkVboCompo);
            bundle->add(type, vboCompo);
            break;
        }
        case FkPluginRequirements::Type::GL_MATRIX: {
            auto matCompo = FK_FIND_COMPO(proto->materials, FkMatCompo);
            bundle->add(type, matCompo);
            break;
        }
        case FkPluginRequirements::Type::GL_OUTPUT:
            bundle->add(type, device->texArray());
            break;
    }
    return 0;
}

/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#include "FkGraphicRenderAtom.h"
#include "FkRenderRequestPrt.h"
#include "FkEmptyQuark.h"
#include "FkDeviceEntity.h"
#include "FkImageContext.h"
#include "FkMatCompo.h"
#include "FkSizeCompo.h"
#include "FkPointFCompo.h"
#include "FkPointVertexCompo.h"
#include "FkReadPixelsProto.h"
#include "FkFuncCompo.h"
#include "FkPathCompo.h"
#include "FkScaleComponent.h"
#include "FkTexEntity.h"
#include "FkCropComponent.h"
#include "FkImageSourceCompo.h"
#include "FkBackgroundColorCompo.h"
#include "FkPluginCompo.h"
#include "FkTransMatCompo.h"

FK_IMPL_CLASS_TYPE(FkGraphicRenderAtom, FkSimpleAtom)

FkGraphicRenderAtom::FkGraphicRenderAtom() : FkSimpleAtom() {

}

FkGraphicRenderAtom::~FkGraphicRenderAtom() {

}

void FkGraphicRenderAtom::describeProtocols(std::shared_ptr<FkPortDesc> desc) {
    FK_PORT_DESC_QUICK_ADD(desc, FkRenderRequestPrt, FkGraphicRenderAtom::_onRenderRequest);
    FK_PORT_DESC_QUICK_ADD(desc, FkReadPixelsProto, FkGraphicRenderAtom::_onReadPixels);
}

void FkGraphicRenderAtom::onConnect(std::shared_ptr<FkConnectChain> chain) {
    chain->next<FkEmptyQuark>();
}

FkResult FkGraphicRenderAtom::onCreate() {
    return FkSimpleAtom::onCreate();
}

FkResult FkGraphicRenderAtom::onDestroy() {
    return FkSimpleAtom::onDestroy();
}

FkResult FkGraphicRenderAtom::onStart() {
    return FkSimpleAtom::onStart();
}

FkResult FkGraphicRenderAtom::onStop() {
    return FkSimpleAtom::onStop();
}

FkResult FkGraphicRenderAtom::_onRenderRequest(std::shared_ptr<FkProtocol> p) {
    FK_CAST_NULLABLE_PTR_RETURN_INT(proto, FkRenderRequestPrt, p);
    FK_CAST_NULLABLE_PTR_RETURN_INT(context, FkImageContext, getContext());
    auto renderEngine = context->getRenderEngine();
    FkAssert(renderEngine != nullptr, FK_NPE);
    auto canvas = proto->req->getCanvas();
    auto canvasSizeCompo = FK_FIND_COMPO(canvas, FkSizeCompo);
    if (canvasSizeCompo) {
        renderEngine->updateMaterial(canvas->material, canvasSizeCompo->size, FkColor::transparent());
    }
    bool isRenderOnce = proto->req->strategy.isOnce && !proto->req->strategy.outSize.isZero() && proto->req->strategy.buf;
    if (isRenderOnce) {
        canvas->material = renderEngine->addMaterial();
        auto ret = renderEngine->updateMaterial(canvas->material,
                                                proto->req->strategy.outSize,
                                                FkColor::black());
        FkAssert(ret == FK_OK, ret);
    }
    auto request = std::make_shared<FkRenderDeviceRequest>(++renderReqId);
    for (auto &layer : proto->req->layers) {
        if (Fk_CANVAS_ID == layer->id) {
            continue;
        }
        _makeDrawPointsRequest(layer, request);
        _makeDrawPathsRequest(layer, request);
        auto materials = _makeRenderMaterials(layer);
        if (materials) {
            std::shared_ptr<FkDeviceEntity> device = std::make_shared<FkTexDeviceEntity>(canvas->material);
            auto ret = request->add(materials, device);
            FkAssert(FK_OK == ret, ret);
        } else {
            FkLogW(FK_DEF_TAG, "Skip render layer %d", layer->id);
        }
    }
    if (isRenderOnce) {
        auto bufDevice = std::make_shared<FkBufDeviceEntity>(proto->req->strategy.buf);
        bufDevice->setPosition(0, 0);
        bufDevice->setSize(proto->req->strategy.outSize);
        std::shared_ptr<FkDeviceEntity> device = bufDevice;
        device->addComponent(std::make_shared<FkFuncCompo>(proto->req->strategy.doneFunc));
        std::shared_ptr<FkMaterialEntity> materials = std::make_shared<FkTexEntity>(canvas->material);
        request->add(materials, device);
    } else {
        _makeDrawCanvasRequest(canvas, request);
    }
    auto ret = renderEngine->renderDevice(request);
    if (isRenderOnce) {
        renderEngine->removeMaterial(canvas->material);
    }
    FkAssert(FK_OK == ret, ret);
    return ret;
}

std::shared_ptr<FkMaterialEntity>
FkGraphicRenderAtom::_makeRenderMaterials(std::shared_ptr<FkGraphicLayer> &layer) {
    auto matCompo = FK_FIND_COMPO(layer, FkMatCompo);
    auto scaleCompo = FK_FIND_COMPO(layer, FkScaleComponent);
    if (matCompo) {
        auto materials = std::make_shared<FkTexEntity>(layer->material);
        materials->addComponent(matCompo);
        if (scaleCompo) {
            materials->scale = scaleCompo->value;
        }
        auto cropCompo = FK_FIND_COMPO(layer, FkCropComponent);
        if (cropCompo) {
            materials->addComponent(cropCompo);
        }
        materials->copyComponentFrom(layer, FkTransMatCompo_Class::type);
        materials->copyComponentFrom(layer, FkImageSourceCompo_Class::type);
        materials->copyComponentFrom(layer, FkBackgroundColorCompo_Class::type);
        materials->copyComponentFrom(layer, FkPluginCompo_Class::type);
        return materials;
    }
    return nullptr;
}

FkResult FkGraphicRenderAtom::_makeDrawCanvasRequest(std::shared_ptr<FkGraphicLayer> &canvas,
                                                     std::shared_ptr<FkRenderDeviceRequest> &request) {
    FK_CAST_NULLABLE_PTR_RETURN_INT(context, FkImageContext, getContext());
    auto renderEngine = context->getRenderEngine();
    FkAssert(renderEngine != nullptr, FK_NPE);
    auto materials = _makeRenderMaterials(canvas);
    if (materials) {
        std::shared_ptr<FkDeviceEntity> device = std::make_shared<FkScreenEntity>();
        return request->add(materials, device);
    } else {
        FkLogW(FK_DEF_TAG, "Skip render canvas %d");
    }
    return FK_FAIL;
}

FkResult FkGraphicRenderAtom::_makeDrawPointsRequest(std::shared_ptr<FkGraphicLayer> &layer,
                                                     std::shared_ptr<FkRenderDeviceRequest> &request) {
    std::vector<std::shared_ptr<FkComponent>> vec;
    if (FK_OK != layer->findComponents(vec, FkPointFCompo_Class::type)) {
        return FK_FAIL;
    }
    std::unordered_map<int64_t, std::vector<float>> map;
    for (auto &it : vec) {
        auto point = std::dynamic_pointer_cast<FkPointFCompo>(it);
        auto color = point->color.toInt();
        int64_t key = point->size;
        key = (key << 32);
        key |= (color & 0x00000000FFFFFFFF);
        map[key].emplace_back(point->value.x);
        map[key].emplace_back(point->value.y);
    }

    for (auto &itr : map) {
        auto key = itr.first;
        auto pointCompo = std::make_shared<FkPointFCompo>();
        pointCompo->size = key >> 32;
        pointCompo->color = FkColor::makeFrom((int32_t) (key & 0x00000000FFFFFFFF));
        auto vertex = std::make_shared<FkPointVertexCompo>();
        vertex->setup(itr.second.size() / 2, 2,
                      sizeof(float), itr.second.data());
        std::shared_ptr<FkMaterialEntity> materials = std::make_shared<FkTexEntity>(layer->material);
        materials->addComponent(vertex);
        materials->addComponent(pointCompo);

        std::shared_ptr<FkDeviceEntity> device = std::make_shared<FkTexDeviceEntity>(layer->material);
        return request->add(materials, device);
    }
    return FK_OK;
}

FkResult FkGraphicRenderAtom::_onReadPixels(std::shared_ptr<FkProtocol> &p) {
    FK_CAST_NULLABLE_PTR_RETURN_INT(proto, FkReadPixelsProto, p);
    FkAssert(proto->layer != nullptr, FK_NPE);
    FK_CAST_NULLABLE_PTR_RETURN_INT(context, FkImageContext, getContext());
    auto renderEngine = context->getRenderEngine();
    FkAssert(renderEngine != nullptr, FK_NPE);
    std::shared_ptr<FkMaterialEntity> materials = std::make_shared<FkTexEntity>(proto->layer->material);
    if (proto->size.isZero()) {
        auto sizeCompo = FK_FIND_COMPO(proto->layer, FkSizeCompo);
        proto->size = sizeCompo->size;
    }
    proto->buf = FkBuffer::alloc(proto->size.getWidth() * proto->size.getHeight() * 4);

    auto promise = std::make_shared<std::promise<int>>();
    auto bufDevice = std::make_shared<FkBufDeviceEntity>(proto->buf);
    bufDevice->setPosition(proto->pos.x, proto->pos.y);
    bufDevice->setSize(proto->size);
    std::shared_ptr<FkDeviceEntity> device = bufDevice;
    device->addComponent(std::make_shared<FkFuncCompo>([promise]() {
        promise->set_value(FK_OK);
    }));
    auto ret = renderEngine->renderDevice(materials, device);
    if (FK_OK != ret || FK_OK != promise->get_future().get()) {
        proto->buf = nullptr;
    }
    if (proto->finishCallback) {
        proto->finishCallback(proto->buf, proto->size);
        proto->finishCallback = nullptr;
    }
    return ret;
}

FkResult FkGraphicRenderAtom::_makeDrawPathsRequest(std::shared_ptr<FkGraphicLayer> &layer,
                                                    std::shared_ptr<FkRenderDeviceRequest> &request) {
    std::vector<std::shared_ptr<FkComponent>> paths;
    if (layer->findComponents(paths, FkPathCompo_Class::type) == FK_OK) {
        std::shared_ptr<FkMaterialEntity> materials = std::make_shared<FkTexEntity>(layer->material);
        materials->addComponents(paths);

        std::shared_ptr<FkDeviceEntity> device = std::make_shared<FkTexDeviceEntity>(layer->material);
        return request->add(materials, device);
    }
    return FK_FAIL;
}

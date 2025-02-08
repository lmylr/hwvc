/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: Alimin
* CREATE TIME: 2022-2-27 13:47:00
*/

#include "FkRenderVboQuark.h"
#include "FkRenderProto.h"
#include "FkTexEntity.h"
#include "FkVertexCompo.h"
#include "FkCoordinateCompo.h"
#include "FkVboCompo.h"
#include "FkPointFCompo.h"
#include "FkCropComponent.h"
#include "FkImageSourceCompo.h"

//每个点占多少字节
#define SIZE_OF_VERTEX  sizeof(float)
//多少个坐标
#define COUNT_VERTEX  4
//每个坐标的维度
#define COUNT_PER_VERTEX  2

FK_IMPL_CLASS_TYPE(FkRenderVboQuark, FkQuark)

FkRenderVboQuark::FkRenderVboQuark() : FkQuark() {

}

FkRenderVboQuark::~FkRenderVboQuark() {

}

void FkRenderVboQuark::describeProtocols(std::shared_ptr<FkPortDesc> desc) {
    FK_PORT_DESC_QUICK_ADD(desc, FkRenderProto, FkRenderVboQuark::_onRender);
}

FkResult FkRenderVboQuark::onCreate() {
    return FkQuark::onCreate();
}

FkResult FkRenderVboQuark::onDestroy() {
    return FkQuark::onDestroy();
}

FkResult FkRenderVboQuark::onStart() {
    auto ret = FkQuark::onStart();
    if (FK_OK != ret) {
        return ret;
    }
    allocator = std::make_shared<FkVertexObjectAllocator>(4 * 2 * sizeof(float) * 10);
    return ret;
}

FkResult FkRenderVboQuark::onStop() {
    allocator->release();
    allocator = nullptr;
    return FkQuark::onStop();
}

FkResult FkRenderVboQuark::_onRender(std::shared_ptr<FkProtocol> &p) {
    FK_CAST_NULLABLE_PTR_RETURN_INT(proto, FkRenderProto, p);
    auto material = std::dynamic_pointer_cast<FkTexEntity>(proto->materials);
    std::shared_ptr<FkVertexCompo> vertexCompo = nullptr;
    auto cropCompo = FK_FIND_COMPO(material, FkCropComponent);
    auto imageSourceCompo = FK_FIND_COMPO(material, FkImageSourceCompo);
    if (material) {
        auto size = material->texArray()->size;
        if (cropCompo) {
            size.set(cropCompo->rect.getWidth(), cropCompo->rect.getHeight());
        }
        vertexCompo = std::make_shared<FkVertexCompo>(size);
    }
    auto rectF = FkFloatRect(0.0f, 1.0f, 1.0f, 0.0f);
    if (cropCompo && material) {
        auto size = material->texArray()->size;
        auto cropRect = cropCompo->rect;
        rectF = FkFloatRect(cropRect.left() * 1.0f / size.getWidth(),
                            cropRect.bottom() * 1.0f / size.getHeight(),
                            cropRect.right() * 1.0f / size.getWidth(),
                            cropRect.top() * 1.0f / size.getHeight());
    }
    auto coordCompo = std::make_shared<FkCoordinateCompo>(rectF);

    FkVBODescription desc(vertexCompo->size() + coordCompo->size());
    auto comp = std::make_shared<FkVboCompo>();
    comp->setup(allocator->alloc(desc),
                static_cast<float *>(vertexCompo->data()), vertexCompo->desc,
                static_cast<float *>(coordCompo->data()), coordCompo->desc);
    proto->materials->addComponent(comp);

    return FK_OK;
}
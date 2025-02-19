/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: Alimin
* CREATE TIME: 2022-2-26 20:39:39
*/

#include "FkRenderFboQuark.h"
#include "FkRenderProto.h"
#include "FkNewTexProto.h"
#include "FkFboCompo.h"
#include "FkNewBmpTexProto.h"
#include "FkNewImageSourceTexProto.h"

FK_IMPL_CLASS_TYPE(FkRenderFboQuark, FkQuark)

FkRenderFboQuark::FkRenderFboQuark() : FkQuark() {

}

FkRenderFboQuark::~FkRenderFboQuark() {

}
void FkRenderFboQuark::describeProtocols(std::shared_ptr<FkPortDesc> desc) {
    FK_PORT_DESC_QUICK_ADD(desc, FkRenderProto, FkRenderFboQuark::_onRender);
    FK_PORT_DESC_QUICK_ADD(desc, FkNewTexProto, FkRenderFboQuark::_onWithFbo);
    FK_PORT_DESC_QUICK_ADD(desc, FkNewBmpTexProto, FkRenderFboQuark::_onWithFbo);
    FK_PORT_DESC_QUICK_ADD(desc, FkNewImageSourceTexProto, FkRenderFboQuark::_onWithFbo);
}

FkResult FkRenderFboQuark::onCreate() {
    return FkQuark::onCreate();
}

FkResult FkRenderFboQuark::onDestroy() {
    return FkQuark::onDestroy();
}

FkResult FkRenderFboQuark::onStart() {
    auto ret = FkQuark::onStart();
    if (FK_OK != ret) {
        return ret;
    }
    fboAllocator = std::make_shared<FkGraphicFBOAllocator>(10);
    return ret;
}

FkResult FkRenderFboQuark::onStop() {
    fboAllocator->release();
    fboAllocator = nullptr;
    return FkQuark::onStop();
}

FkResult FkRenderFboQuark::_onRender(std::shared_ptr<FkProtocol> &p) {
    FK_CAST_NULLABLE_PTR_RETURN_INT(proto, FkRenderProto, p);
    int32_t desc = 0;
    auto fbo = fboAllocator->alloc(desc);
    if (fbo == nullptr) {
        return FK_SOURCE_NOT_FOUND;
    }
    auto compo = std::make_shared<FkFboCompo>(fbo);
    proto->materials->addComponent(compo);
    return FK_OK;
}

FkResult FkRenderFboQuark::_onWithFbo(std::shared_ptr<FkProtocol> &p) {
    FK_CAST_NULLABLE_PTR_RETURN_INT(proto, FkNewTexProto, p);
    int32_t desc = 0;
    auto fbo = fboAllocator->alloc(desc);
    if (fbo) {
        auto compo = std::make_shared<FkFboCompo>(fbo);
        proto->texEntity->addComponent(compo);
    }
    return FK_OK;
}

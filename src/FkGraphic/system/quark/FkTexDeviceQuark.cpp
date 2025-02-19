/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: Alimin
* CREATE TIME: 2022-2-27 12:55:44
*/

#include "FkTexDeviceQuark.h"
#include "FkRenderProto.h"
#include "FkTexDeviceQuark.h"
#include "FkTexEntity.h"
#include "FkVboCompo.h"
#include "FkRenderProgramCompo.h"
#include "FkGLDefinition.h"
#include "FkMatCompo.h"
#include "FkTexCompo.h"
#include "FkBitmap.h"
#include "FkString.h"
#include "FkMVPMatrix.h"
#include "FkViewportMatCompo.h"
#include "FkImageSourceCompo.h"
#include "FkTransMatCompo.h"

FK_IMPL_CLASS_TYPE(FkTexDeviceQuark, FkQuark)

FkTexDeviceQuark::FkTexDeviceQuark() : FkQuark() {

}

FkTexDeviceQuark::~FkTexDeviceQuark() {

}

void FkTexDeviceQuark::describeProtocols(std::shared_ptr<FkPortDesc> desc) {
    FK_PORT_DESC_QUICK_ADD(desc, FkRenderProto, FkTexDeviceQuark::_onRender);
}

FkResult FkTexDeviceQuark::onCreate() {
    auto ret = FkQuark::onCreate();
    if (FK_OK != ret) {
        return ret;
    }
    return ret;
}

FkResult FkTexDeviceQuark::onDestroy() {
    auto ret = FkQuark::onDestroy();
    if (FK_OK != ret) {
        return ret;
    }
    return ret;
}

FkResult FkTexDeviceQuark::onStart() {
    auto ret = FkQuark::onStart();
    if (FK_OK != ret) {
        return ret;
    }
    return ret;
}

FkResult FkTexDeviceQuark::onStop() {
    return FkQuark::onStop();
}

FkResult FkTexDeviceQuark::_onRender(std::shared_ptr<FkProtocol> p) {
    FK_CAST_NULLABLE_PTR_RETURN_INT(proto, FkRenderProto, p);
    if (!FK_INSTANCE_OF(proto->device, FkTexDeviceEntity)) {
        return FK_SKIP;
    }
    FK_CAST_NULLABLE_PTR_RETURN_INT(device, FkTexDeviceEntity, proto->device);
    FK_CAST_NULLABLE_PTR_RETURN_INT(material, FkTexEntity, proto->materials);
    auto srcTexArray = material->texArray();
    auto fboCompo = material->fbo();
    auto dstTexArray = device->texArray();
    if (dstTexArray->empty()) {
        FkLogW(FK_DEF_TAG, "Not support for multi-texture frame buffer object.");
        return FK_SKIP;
    }
    auto size = device->size();

    auto programCompo = FK_FIND_COMPO(proto->materials, FkRenderProgramCompo);
    auto vboCompo = FK_FIND_COMPO(proto->materials, FkVboCompo);
    auto matCompo = FK_FIND_COMPO(proto->materials, FkMatCompo);
    FkAssert(vboCompo != nullptr, FK_FAIL);

    int32_t offset = 0;
    FkVertexDesc desc;
    if (FK_OK != vboCompo->getValueLoc(FkVboCompo::kValueLoc::VERTEX, offset, desc)) {
        FkLogW(FK_DEF_TAG, "Get vertex count error.");
    }
    auto imageSourceCompo = FK_FIND_COMPO(proto->materials, FkImageSourceCompo);
    auto transMatCompo = FK_FIND_COMPO(proto->materials, FkTransMatCompo);
    if (imageSourceCompo) {
        if (transMatCompo && transMatCompo->value && transMatCompo->value->isZero()) {
            imageSourceCompo->value->onRender(srcTexArray->textures[0]->tex, proto->reqId, "");
            FkLogW(FK_DEF_TAG, "Skip source render cause by zero matrix.");
            return FK_SKIP;
        }
    }

    glEnable(GL_BLEND);
    /**
     * Texture must be premultiplied
     * sfactor: texture
     * dfactor: frame buffer
     * blendColor = srcColor * sfactor + dstColor * dfactor
     * example:
     * glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)
     * > blendColor.r = srcColor.a * srcColor.r + (1-srcColor.a) * dstColor.r
     * > blendColor.g = srcColor.a * srcColor.g + (1-srcColor.a) * dstColor.g
     * > blendColor.b = srcColor.a * srcColor.b + (1-srcColor.a) * dstColor.b
     * > blendColor.a = srcColor.a * srcColor.a + (1-srcColor.a) * dstColor.a
     */
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquation(GL_FUNC_ADD);

#if defined(__FK_DEBUG__)
    auto status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    FkAssert(GL_FRAMEBUFFER_COMPLETE == status,);
#endif
    vboCompo->bind();
    FK_GL_CHECK(programCompo->program->bind());
    fboCompo->fbo->bind();
    programCompo->program->addValue(srcTexArray);
    programCompo->program->addValue(matCompo);
    programCompo->program->addValue(vboCompo);
    if (transMatCompo) {
        programCompo->program->addValue(transMatCompo);
    }
    FkIntVec2 pos(0, 0);
    for (int y = 0; y < dstTexArray->blocks.y; ++y) {
        pos.x = 0;
        for (int x = 0; x < dstTexArray->blocks.x; ++x) {
            int index = y * dstTexArray->blocks.x + x;
            auto tex = (*dstTexArray)[index];
            auto compo = std::make_shared<FkViewportMatCompo>();
            compo->value = dstTexArray->calcViewportMatrix(index, pos);
            programCompo->program->addValue(compo);

            glViewport(0, 0, tex->desc.size.getWidth(), tex->desc.size.getHeight());
            fboCompo->fbo->attach(tex);
            FK_GL_CHECK(glDrawArrays(GL_TRIANGLE_STRIP, 0, desc.countVertex));
#if 0
            auto buf = FkBuffer::alloc(tex->desc.size.getWidth() * tex->desc.size.getHeight() * 4);
            glReadPixels(0, 0,
                         tex->desc.size.getWidth(), tex->desc.size.getHeight(),
                         GL_RGBA, GL_UNSIGNED_BYTE, buf->data());
            FkString path("/storage/emulated/0/Android/data/com.alimin.pic/cache/image_sub_");
            path.append(index);
            path.append(".jpg");
            auto ret = FkBitmap::write(path.c_str(), FkImage::Format::kJPEG, buf, tex->desc.size, 80);
            FkLogI("filmkilns", "%d, %d, %dx%d", index, ret, tex->desc.size.getWidth(), tex->desc.size.getHeight());
#endif

            fboCompo->fbo->detach(tex->desc.target);
            if (dstTexArray->blocks.x == x + 1) {
                pos.y += tex->desc.size.getHeight();
            }
            pos.x += tex->desc.size.getWidth();
        }
    }
    FK_GL_CHECK(programCompo->program->clear());
    fboCompo->fbo->unbind();
    programCompo->program->unbind();
    vboCompo->unbind();
    glDisable(GL_BLEND);
    if (imageSourceCompo) {
        imageSourceCompo->value->onRender(srcTexArray->textures[0]->tex, proto->reqId, "");
    }
    return FK_OK;
}
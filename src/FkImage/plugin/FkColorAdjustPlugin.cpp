/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: aliminabc@gmail.com

* CREATE TIME: 2024-06-08 00:07:26
*/

#include "FkColorAdjustPlugin.h"
#include "FkGraphicColorAdjustProgram.h"
#include "FkTexArrayCompo.h"
#include "FkFboCompo.h"
#include "FkVboCompo.h"
#include "FkMatCompo.h"
#include "FkTransMatCompo.h"
#include "FkViewportMatCompo.h"
#include "FkAbsImageSource.h"
#include "FkColorAdjustCompo.h"

#define TAG "FkColorAdjustPlugin"

FK_IMPL_CLASS_TYPE(FkColorAdjustPlugin, FkAbsPlugin)

FkColorAdjustPlugin::FkColorAdjustPlugin() : FkAbsPlugin() {
    updateParams({{"brightness", 0.0f},
                  {"contrast",   1.0f},
                  {"saturation", 1.0f}});
}

FkColorAdjustPlugin::~FkColorAdjustPlugin() {

}

FkResult FkColorAdjustPlugin::onCreate() {
    FkLogI(TAG, "onCreate");
    FkProgramDescription desc(FkProgramDescription::kType::COLOR_ADJUST);
    program = std::make_shared<FkGraphicColorAdjustProgram>(desc);
    return program->create();
}

FkResult FkColorAdjustPlugin::onDestroy() {
    FkLogI(TAG, "onDestroy");
    program->destroy();
    return FK_OK;
}

FkPluginRequirements FkColorAdjustPlugin::describeRequirements() {
    FkPluginRequirements requirements;
    requirements.add(FkPluginRequirements::Type::GL_FBO);
    requirements.add(FkPluginRequirements::Type::GL_INPUT);
    requirements.add(FkPluginRequirements::Type::GL_INPUT_IMAGE);
    requirements.add(FkPluginRequirements::Type::GL_VBO);
    requirements.add(FkPluginRequirements::Type::GL_MATRIX);
    requirements.add(FkPluginRequirements::Type::GL_OUTPUT);
    requirements.add(FkPluginRequirements::Type::THREAD_GL);
    return requirements;
}

FkResult FkColorAdjustPlugin::onPreProcess() {
    return FK_OK;
}

FkResult FkColorAdjustPlugin::onProcess(const std::shared_ptr<FkPluginBundle> &bundle) {
    if (bundle->size() == 0) {
        return FK_FAIL;
    }
    auto srcTexArray = std::any_cast<std::shared_ptr<FkTexArrayCompo>>(bundle->get(FkPluginRequirements::Type::GL_INPUT));
    auto fboCompo = std::any_cast<std::shared_ptr<FkFboCompo>>(bundle->get(FkPluginRequirements::Type::GL_FBO));
    auto dstTexArray = std::any_cast<std::shared_ptr<FkTexArrayCompo>>(bundle->get(FkPluginRequirements::Type::GL_OUTPUT));
    if (dstTexArray->empty()) {
        FkLogW(FK_DEF_TAG, "Not support for multi-texture frame buffer object.");
        return FK_SKIP;
    }

    auto vboCompo = std::any_cast<std::shared_ptr<FkVboCompo>>(bundle->get(FkPluginRequirements::Type::GL_VBO));
    auto matCompo = std::any_cast<std::shared_ptr<FkMatCompo>>(bundle->get(FkPluginRequirements::Type::GL_MATRIX));
    auto transMatCompo = std::any_cast<std::shared_ptr<FkTransMatCompo>>(bundle->get(FkPluginRequirements::Type::GL_TRANS_MATRIX));
    FkAssert(vboCompo != nullptr, FK_FAIL);

    int32_t offset = 0;
    FkVertexDesc desc;
    if (FK_OK != vboCompo->getValueLoc(FkVboCompo::kValueLoc::VERTEX, offset, desc)) {
        FkLogW(FK_DEF_TAG, "Get vertex count error.");
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
    FK_GL_CHECK(program->bind());
    fboCompo->fbo->bind();
    program->addValue(srcTexArray);
    program->addValue(matCompo);
    program->addValue(vboCompo);
    auto colorAdjustCompo = std::make_shared<FkColorAdjustCompo>();
    colorAdjustCompo->brightness = getParam("brightness").getFloat();
    colorAdjustCompo->contrast = getParam("contrast").getFloat();
    colorAdjustCompo->saturation = getParam("saturation").getFloat();
    program->addValue(colorAdjustCompo);
    if (transMatCompo) {
        program->addValue(transMatCompo);
    }
    FkIntVec2 pos(0, 0);
    for (int y = 0; y < dstTexArray->blocks.y; ++y) {
        pos.x = 0;
        for (int x = 0; x < dstTexArray->blocks.x; ++x) {
            int index = y * dstTexArray->blocks.x + x;
            auto tex = (*dstTexArray)[index];
            auto compo = std::make_shared<FkViewportMatCompo>();
            compo->value = dstTexArray->calcViewportMatrix(index, pos);
            program->addValue(compo);

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
            FkLogI("aliminabc", "%d, %d, %dx%d", index, ret, tex->desc.size.getWidth(), tex->desc.size.getHeight());
#endif

            fboCompo->fbo->detach(tex->desc.target);
            if (dstTexArray->blocks.x == x + 1) {
                pos.y += tex->desc.size.getHeight();
            }
            pos.x += tex->desc.size.getWidth();
        }
    }
    FK_GL_CHECK(program->clear());
    fboCompo->fbo->unbind();
    program->unbind();
    vboCompo->unbind();
    glDisable(GL_BLEND);
    return FK_OK;
}

FkResult FkColorAdjustPlugin::onPostProcess() {
    return FK_OK;
}

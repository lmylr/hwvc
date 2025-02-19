/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns)

* CREATE TIME: 2024-07-15 23:18:37
*/

#include "FkHistPlugin.h"
#include "FkGLDefinition.h"
#include "FkGraphicHistViewProgram.h"
#include "FkGraphicHistCalcProgram.h"
#include "FkGraphicAndroidHistCalcProgram.h"
#include "FkDrawHistMatProgram.h"
#include "FkTexArrayCompo.h"
#include "FkFboCompo.h"
#include "FkVboCompo.h"
#include "FkTransMatCompo.h"
#include "FkViewportMatCompo.h"
#include "FkTransMatCompo.h"
#include "FkGLMatrix.h"
#include "FkVertexCompo.h"
#include "FkCoordinateCompo.h"
#include "FkRenderProgramCompo.h"
#include "FkMath.h"
#include "FkMVPMatrix.h"
#include "FkBitmapDefinition.h"

#define TAG "FkHistPlugin"

FK_IMPL_CLASS_TYPE(FkHistPlugin, FkAbsPlugin)

FkHistPlugin::FkHistPlugin() : FkAbsPlugin() {
    updateParams({{"scale", 1.0f},
                  {"ratio", 1.0f},
                  {"location", (int) FkEncodedOrigin::kCenter}});
}

FkHistPlugin::~FkHistPlugin() {

}

std::shared_ptr<FkGraphicTexture> FkHistPlugin::_createTex(FkSize size, uint64_t flags, FkColor::kFormat fmt) {
    FkTexDescription texDesc(GL_TEXTURE_2D);
    texDesc.filterMode = FkTexDescription::kFilterMode::NEAREST;
    texDesc.size = size;
    texDesc.fmt = fmt;
    texDesc.flags = flags;
    auto tex = std::make_shared<FkGraphicTexture>(texDesc);
    if (tex->create() == FK_OK && !size.isZero()) {
        tex->update(nullptr);
    }
    return tex;
}

std::shared_ptr<FkVboCompo> FkHistPlugin::_createVBO(const FkSize &size) {
    std::shared_ptr<FkVertexCompo> vertexCompo = std::make_shared<FkVertexCompo>(size);
    auto rectF = FkFloatRect(0.0f, 1.0f, 1.0f, 0.0f);
    auto coordCompo = std::make_shared<FkCoordinateCompo>(rectF);

    FkVBODescription desc(vertexCompo->size() + coordCompo->size());
    auto compo = std::make_shared<FkVboCompo>();
    compo->setup(allocator->alloc(desc),
                 static_cast<float *>(vertexCompo->data()), vertexCompo->desc,
                 static_cast<float *>(coordCompo->data()), coordCompo->desc);
    return compo;
}

FkResult FkHistPlugin::_createCalcProgram(uint32_t target) {
    GLint values[2];
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, values);

    FkProgramDescription desc(FkProgramDescription::kType::HIST_CALC);
    desc.maxCountOfFragmentTexture = values[0];
    if (target == GL_TEXTURE_EXTERNAL_OES) {
        desc.type = FkProgramDescription::kType::HIST_CALC_ANDROID;
    } else {
        desc.type = FkProgramDescription::kType::HIST_CALC;
    }
    if (calcProgram && calcProgram->desc.type != desc.type) {
        calcProgram->destroy();
        calcProgram = nullptr;
    }
    if (calcProgram == nullptr) {
        if (desc.type == FkProgramDescription::kType::HIST_CALC_ANDROID) {
            calcProgram = std::make_shared<FkGraphicAndroidHistCalcProgram>(desc);
        } else {
            calcProgram = std::make_shared<FkGraphicHistCalcProgram>(desc);
        }
        calcProgram->create();
    }
    return FK_OK;
}

FkResult FkHistPlugin::onCreate() {
    FkLogI(TAG, "onCreate");
    allocator = std::make_shared<FkVertexObjectAllocator>(4 * 2 * sizeof(float) * 10);
    FkProgramDescription desc(FkProgramDescription::kType::DRAW_HIST_MAT);
    viewProgram = std::make_shared<FkDrawHistMatProgram>(desc);
    viewProgram->create();
    _createHistBuffer();
    FkSize size(256, 256);
    histTex = _createTex(size, FkTexDescription::FLAG_NONE, FkColor::kFormat::RGBA);
    histVBOCompo = _createVBO(size);
    return FK_OK;
}

FkResult FkHistPlugin::_createHistBuffer() {
    if (histBuf != GL_NONE) {
        glDeleteBuffers(1, &histBuf);
        histBuf = GL_NONE;
    }
    glGenBuffers(1, &histBuf);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, histBuf);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(GLint) * 256 * 4, nullptr, GL_DYNAMIC_COPY);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, GL_NONE);

    glGenBuffers(1, &histInfoBuf);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, histInfoBuf);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(GLint), nullptr, GL_DYNAMIC_COPY);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, GL_NONE);
    return FK_OK;
}

FkResult FkHistPlugin::_resetHistBuffer() {
    int histBufData[256 * 4]{0};
    int histInfoBufData[1]{0};
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, histBuf);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(GLint) * 256 * 4, histBufData, GL_DYNAMIC_COPY);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, histInfoBuf);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(GLint), histInfoBufData, GL_DYNAMIC_COPY);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, GL_NONE);
    return FK_OK;
}

FkResult FkHistPlugin::onDestroy() {
    FkLogI(TAG, "onDestroy");
    histMVPCompo = nullptr;
    histVBOCompo = nullptr;
    histTex->destroy();
    histTex = nullptr;
    if (histInfoBuf != GL_NONE) {
        glDeleteBuffers(1, &histInfoBuf);
        histInfoBuf = GL_NONE;
    }
    if (histBuf != GL_NONE) {
        glDeleteBuffers(1, &histBuf);
        histBuf = GL_NONE;
    }
    calcProgram->destroy();
    viewProgram->destroy();
    allocator->release();
    allocator = nullptr;
    return FK_OK;
}

FkPluginRequirements FkHistPlugin::describeRequirements() {
    FkPluginRequirements requirements;
    requirements.add(FkPluginRequirements::Type::GL_FBO);
    requirements.add(FkPluginRequirements::Type::GL_INPUT);
    requirements.add(FkPluginRequirements::Type::GL_INPUT_IMAGE);
    requirements.add(FkPluginRequirements::Type::GL_VBO);
    requirements.add(FkPluginRequirements::Type::GL_MATRIX);
    requirements.add(FkPluginRequirements::Type::GL_OUTPUT);
    requirements.add(FkPluginRequirements::Type::THREAD_GL);
    requirements.add(FkPluginRequirements::Type::GL_PROGRAM);
    return requirements;
}

FkResult FkHistPlugin::onPreProcess() {
    return FK_OK;
}

FkResult FkHistPlugin::onProcess(const std::shared_ptr<FkPluginBundle> &bundle) {
    if (bundle->size() == 0) {
        return FK_FAIL;
    }
    auto srcTexArray = std::any_cast<std::shared_ptr<FkTexArrayCompo>>(bundle->get(FkPluginRequirements::Type::GL_INPUT));
    if (srcTexArray) {
        _createCalcProgram((*srcTexArray)[0]->desc.target);
    }
    auto fboCompo = std::any_cast<std::shared_ptr<FkFboCompo>>(bundle->get(FkPluginRequirements::Type::GL_FBO));
    _resetHistBuffer();
    _calcHistogramV2(srcTexArray, fboCompo);
    _copyHistBuf2Tex();
    FkLogD(TAG, "Texture len=%d, size=%dx%d, block=%dx%d", srcTexArray->textures.size(),
           srcTexArray->size.getWidth(), srcTexArray->size.getHeight(),
           srcTexArray->blockSize.getWidth(), srcTexArray->blockSize.getHeight());
    _updateResult(srcTexArray->size.getWidth() * srcTexArray->size.getHeight());
    return _drawHist2Dst(bundle);
}

void FkHistPlugin::_updateResult(int max) {
    float dart = pixelCnt[0] * 1.0f / max;
    float medium = pixelCnt[1] * 1.0f / max;
    float bright = pixelCnt[2] * 1.0f / max;
    int expValue = 100;
    if (pixelCnt[0] != 0 || pixelCnt[2] != 0) {
        expValue += (pixelCnt[2] - pixelCnt[0]) * 100 / std::max(pixelCnt[2], pixelCnt[0]);
    }
    FkLogD(TAG, "exposure_value %.3f, %.3f, %.3f, %d", dart, medium, bright, expValue);
    updateParams({{"cnt_dart",       pixelCnt[0]},
                  {"cnt_medium",     pixelCnt[1]},
                  {"cnt_bright",     pixelCnt[2]},
                  {"cnt_max",        max},
                  {"exposure_value", expValue}});
}

FkResult FkHistPlugin::_copyHistBuf2Tex() {
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, histInfoBuf);
    int *values = static_cast<int *>(glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0,
                                                      sizeof(GLint), GL_MAP_READ_BIT));
    if (values == nullptr) {
        GLenum e = glGetError();
        FkLogW(TAG, "[FAIL] Read hist buffer error(%i, 0x%x)", e, e);
        return FK_FAIL;
    }
    int maxValue = values[0];
    FK_GL_CHECK(glUnmapBuffer(GL_SHADER_STORAGE_BUFFER));

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, histBuf);
    values = static_cast<int *>(glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0,
                                                 sizeof(GLint) * 256 * 4, GL_MAP_READ_BIT));

    if (bmp == nullptr || bmp->getByteSize() != (histTex->desc.size.getWidth() * histTex->desc.size.getHeight() * 4)) {
        bmp = FkBitmap::create(histTex->desc.size.getWidth(), histTex->desc.size.getHeight());
    }
    auto rgba = bmp->getPixels();
    memset(rgba, 0, bmp->getByteSize());
    memset(pixelCnt, 0, sizeof(pixelCnt));
    for (int i = 0; i < 256; ++i) {
        int offset = i * 256 * 4;
        int greyCnt = values[i + 256 * 2];
        if (i < 30) {
            pixelCnt[0] += greyCnt;
        } else if (i >= 112 && i < 142) {
            pixelCnt[1] += greyCnt;
        } else if (i > 225 && i <= 255) {
            pixelCnt[2] += greyCnt;
        }
        for (int j = 0; j < 256; ++j) {
            uint8_t r = j < (values[i] * 255 / maxValue) ? 255 : 0;
            uint8_t g = j < (values[i + 256 * 1] * 255 / maxValue) ? 255 : 0;
            uint8_t b = j < (values[i + 256 * 2] * 255 / maxValue) ? 255 : 0;
            *(rgba + offset + j * 4) = r;
            *(rgba + offset + j * 4 + 1) = g;
            *(rgba + offset + j * 4 + 2) = b;
            *(rgba + offset + j * 4 + 3) = 255;

            if (r == 0 && g == 0 && b == 0) {
                *(rgba + offset + j * 4 + 3) = 178;
            } else if (r == 255 && g == 255 && b == 255) {
                *(rgba + offset + j * 4) = 94;
                *(rgba + offset + j * 4 + 1) = 122;
                *(rgba + offset + j * 4 + 2) = 93;
            }
        }
    }
    FK_GL_CHECK(glUnmapBuffer(GL_SHADER_STORAGE_BUFFER));
    FK_GL_CHECK(glBindBuffer(GL_SHADER_STORAGE_BUFFER, GL_NONE));
    return histTex->update(rgba);
}

void FkHistPlugin::_resetMVP(FkSize targetSize, float scale, float ratio) {
    histMVPCompo->value->reset();
    histMVPCompo->value->setViewSize(targetSize.getWidth(), targetSize.getHeight());
    histMVPCompo->value->lookAt(FkFloatVec3(0.0f, 0.0f, 1.0f),
                   FkFloatVec3(0.0f, 0.0f, 0.0f),
                   FkFloatVec3(0.0f, 1.0f, 0.0f));
    histMVPCompo->value->setRotation(FkRational(FkMath::PI_R.num, FkMath::PI_R.den * 2));
    float scaleValue = std::min(targetSize.getWidth() * 1.0f / histTex->desc.size.getWidth(), targetSize.getHeight() * 1.0f / histTex->desc.size.getHeight());
    FkFloatVec3 s(scaleValue * scale * ratio, scaleValue * scale, 1.0f);
    histMVPCompo->value->setScale(s);
    FkFloatVec3 trans(0.0f, 0.0f, 0.0f);
    histMVPCompo->value->setTranslate(trans);
}

FkResult FkHistPlugin::_drawHist2Dst(const std::shared_ptr<FkPluginBundle> &bundle) {
    auto vboCompo = histVBOCompo;
    FkAssert(vboCompo != nullptr, FK_FAIL);
    auto fboCompo = std::any_cast<std::shared_ptr<FkFboCompo>>(bundle->get(FkPluginRequirements::Type::GL_FBO));
    auto dstTexArray = std::any_cast<std::shared_ptr<FkTexArrayCompo>>(bundle->get(FkPluginRequirements::Type::GL_OUTPUT));
    if (dstTexArray->empty()) {
        FkLogW(TAG, "Not support for multi-texture frame buffer object.");
        return FK_SKIP;
    }
    if (histMVPCompo == nullptr) {
        histMVPCompo = std::make_shared<FkMatCompo>();
        histMVPCompo->value = std::make_shared<FkMVPMatrix>(FkMVPMatrix::kProjType::ORTHO);
    }
    _resetMVP(dstTexArray->size, getParam("scale").getFloat(), getParam("ratio").getFloat());
    auto matCompo = histMVPCompo;
    auto transMatCompo = std::make_shared<FkTransMatCompo>();
    transMatCompo->value = std::make_shared<FkGLMatrix>();
    FkAssert(vboCompo != nullptr, FK_FAIL);

    int32_t offset = 0;
    FkVertexDesc desc;
    if (FK_OK != vboCompo->getValueLoc(FkVboCompo::kValueLoc::VERTEX, offset, desc)) {
        FkLogW(FK_DEF_TAG, "Get vertex count error.");
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquation(GL_FUNC_ADD);

#if defined(__FK_DEBUG__)
    auto status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    FkAssert(GL_FRAMEBUFFER_COMPLETE == status,);
#endif
    vboCompo->bind();
    FK_GL_CHECK(viewProgram->bind());
    fboCompo->fbo->bind();
    auto histTexArray = std::make_shared<FkTexArrayCompo>(histTex->desc.size, 1, 1,
                                                     histTex->desc.size.getWidth(),
                                                     histTex->desc.size.getHeight());
    histTexArray->textures.emplace_back(histTex);
    viewProgram->addValue(histTexArray);
    viewProgram->addValue(matCompo);
    viewProgram->addValue(vboCompo);
    if (transMatCompo) {
        viewProgram->addValue(transMatCompo);
    }
    FkIntVec2 pos(0, 0);
    for (int y = 0; y < dstTexArray->blocks.y; ++y) {
        pos.x = 0;
        for (int x = 0; x < dstTexArray->blocks.x; ++x) {
            int index = y * dstTexArray->blocks.x + x;
            auto tex = (*dstTexArray)[index];
            auto compo = std::make_shared<FkViewportMatCompo>();
            compo->value = dstTexArray->calcViewportMatrix(index, pos);
            viewProgram->addValue(compo);

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
    FK_GL_CHECK(viewProgram->clear());
    fboCompo->fbo->unbind();
    viewProgram->unbind();
    vboCompo->unbind();
    glDisable(GL_BLEND);
    return FK_OK;
}

FkResult FkHistPlugin::_calcHistogramV2(const std::shared_ptr<FkTexArrayCompo> &texArray,
                                      const std::shared_ptr<FkFboCompo> &fboCompo) {
    FK_GL_CHECK(calcProgram->bind());
    calcProgram->addValue(texArray);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, histBuf);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, histInfoBuf);
    FK_GL_CHECK(glDispatchCompute(texArray->blockSize.getWidth(), texArray->blockSize.getHeight(), texArray->countOfTexture()));
    FK_GL_CHECK(glMemoryBarrier(GL_ALL_BARRIER_BITS));
    FK_GL_CHECK(glBindBuffer(GL_SHADER_STORAGE_BUFFER, GL_NONE));
    FK_GL_CHECK(calcProgram->clear());
    FK_GL_CHECK(calcProgram->unbind());
    return FK_OK;
}

FkResult FkHistPlugin::onPostProcess() {
    return FK_OK;
}
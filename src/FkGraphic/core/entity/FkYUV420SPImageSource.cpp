/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: aliminabc@gmail.com

* CREATE TIME: 2024-06-23 21:17:59
*/

#include "FkYUV420SPImageSource.h"
#include "FkGLDefinition.h"
#include "FkTexArrayCompo.h"
#include "FkVboCompo.h"
#include "FkVertexCompo.h"
#include "FkCoordinateCompo.h"
#include "FkVertexObject.h"
#include "FkGraphicFrameObject.h"
#include "FkRect.h"
#include "FkMath.h"
#include "FkBitmap.h"

FK_IMPL_CLASS_TYPE(FkYUV420SPImageSource, FkBufferedImageSource)

FkYUV420SPImageSource::FkYUV420SPImageSource(const BufferDesc desc)
        : FkBufferedImageSource(desc), planes(desc.planes) {
}

FkYUV420SPImageSource::~FkYUV420SPImageSource() {
}

FkResult FkYUV420SPImageSource::onCreate(int32_t arg0, int64_t arg1, const std::string &arg2) {
    auto ret = FkBufferedImageSource::onCreate(arg0, arg1, arg2);
    auto texArray = std::make_shared<FkTexArrayCompo>(getSize(), 0, 0,
                                                      getSize().getWidth(),
                                                      getSize().getHeight());
    for (int i = 0; i < planes.size(); ++i) {
        FkTexDescription desc(GL_TEXTURE_2D);
        desc.filterMode = FkTexDescription::kFilterMode::LINEAR;
        if (i == 0) {
            desc.size = getSize();
            desc.fmt = FkColor::kFormat::LUMINANCE;
        } else {
            desc.size = FkSize(getSize().getWidth() / 2, getSize().getHeight() / 2);
            desc.fmt = planes.size() == 2 ? FkColor::kFormat::LUMINANCE_ALPHA : FkColor::kFormat::LUMINANCE;
        }
        auto tex = std::make_shared<FkGraphicTexture>(desc);
        tex->create();
        tex->update(planes[i]->data());
        texArray->textures.emplace_back(tex);
    }
    //每个点占多少字节
    int32_t SIZE_OF_VERTEX = sizeof(float);
    //多少个坐标
    int32_t COUNT_VERTEX = 4;
    //每个坐标的维度
    int32_t COUNT_PER_VERTEX = 2;
    float pos[]{
            -1.0f, -1.0f,//LEFT,BOTTOM
            1.0f, -1.0f,//RIGHT,BOTTOM
            -1.0f, 1.0f,//LEFT,TOP
            1.0f, 1.0f//RIGHT,TOP
    };
    auto vertexCompo = std::make_shared<FkVertexCompo>();
    vertexCompo->setup(COUNT_VERTEX, COUNT_PER_VERTEX, SIZE_OF_VERTEX, pos);
    auto rectF = FkFloatRect(0.0f, 1.0f, 1.0f, 0.0f);
    float coordinate[]{
            rectF.left(), rectF.bottom(),//LEFT,BOTTOM
            rectF.right(), rectF.bottom(),//RIGHT,BOTTOM
            rectF.left(), rectF.top(),//LEFT,TOP
            rectF.right(), rectF.top()//RIGHT,TOP
    };
    auto coordCompo = std::make_shared<FkCoordinateCompo>();
    coordCompo->setup(COUNT_VERTEX, COUNT_PER_VERTEX, SIZE_OF_VERTEX, coordinate);
    FkVBODescription vboDesc(vertexCompo->size() + coordCompo->size());
    auto vbo = std::make_shared<FkVertexObject>(vboDesc);
    vbo->create();
    auto vboCompo = std::make_shared<FkVboCompo>();
    vboCompo->setup(vbo,
                static_cast<float *>(vertexCompo->data()), vertexCompo->desc,
                static_cast<float *>(coordCompo->data()), coordCompo->desc);
    int32_t offset = 0;
    FkVertexDesc vertDesc;
    if (FK_OK != vboCompo->getValueLoc(FkVboCompo::kValueLoc::VERTEX, offset, vertDesc)) {
        FkLogW(FK_DEF_TAG, "Get vertex count error.");
    }

    auto fbo = std::make_shared<FkGraphicFrameObject>();
    fbo->create();
    //Render start
    uint32_t target = GL_TEXTURE_2D;
    FkProgramDescription programDesc(FkProgramDescription::kType::YV12);
    std::shared_ptr<FkGraphicYUVProgram> program = std::make_shared<FkGraphicYUVProgram>(programDesc);
    program->create();

    vboCompo->bind();
    FK_GL_CHECK(program->bind());
    fbo->bind();
    program->addValue(texArray);
    program->addValue(vboCompo);
    glViewport(0, 0, getSize().getWidth(), getSize().getHeight());
    fbo->attach(target, arg0);
    FK_GL_CHECK(glDrawArrays(GL_TRIANGLE_STRIP, 0, vertDesc.countVertex));
    fbo->detach(target);
    FK_GL_CHECK(program->clear());
    fbo->unbind();
    program->unbind();
    vboCompo->unbind();

    //Render end
    program->destroy();
    fbo->destroy();
    vbo->destroy();
    for (auto &it: texArray->textures) {
        it->destroy();
    }
    texArray->textures.clear();
    return ret;
}

FkResult FkYUV420SPImageSource::onDestroy() {
    return FK_NOT_SUPPORT;
}

FkResult FkYUV420SPImageSource::onRender(int32_t arg0, int64_t arg1, const std::string &arg2) {
    return FK_NOT_SUPPORT;
}

FkSize FkYUV420SPImageSource::getSize() {
    return FkBufferedImageSource::getSize();
}

std::shared_ptr<FkMatrix> FkYUV420SPImageSource::getTransformMatrix() {
    return matrix;
}

int64_t FkYUV420SPImageSource::getTimestampInNS() {
    return 0;
}

FkTexDescription FkYUV420SPImageSource::getTexDescription() {
    FkTexDescription _desc;
    _desc.target = GL_TEXTURE_2D;
    return _desc;
}

std::shared_ptr<FkBitmap> FkYUV420SPImageSource::toBitmap() {
    return FkBitmap::fromYUV(desc.planes, desc.size, desc.orientation);
}
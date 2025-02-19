/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#include "FkGraphicMatProgram.h"
#include "FkTexCompo.h"
#include "FkVboCompo.h"
#include "FkMatCompo.h"
#include "FkString.h"
#include "FkTexArrayCompo.h"
#include "FkViewportMatCompo.h"
#include "FkTransMatCompo.h"

FK_IMPL_CLASS_TYPE(FkGraphicMatProgram, FkGraphicProgram)

FkGraphicMatProgram::FkGraphicMatProgram(const FkProgramDescription &desc)
        : FkGraphicProgram(desc) {

}

FkGraphicMatProgram::~FkGraphicMatProgram() {

}

FkProgramDescription::kType FkGraphicMatProgram::type() {
    return FkProgramDescription::kType::MATRIX;
}

FkResult FkGraphicMatProgram::create() {
    auto ret = FkGraphicProgram::create();
    if (FK_OK == ret) {
        aPosLoc = getAttribLocation("aPosition");
        FkAssert(aPosLoc >= 0, FK_FAIL);
        for (int i = 0; i < desc.maxCountOfFragmentTexture; ++i) {
            FkString key("uTexture[");
            key.append(i);
            key.append(']');
            auto loc = getUniformLocation(key.str());
            FkAssert(loc >= 0, FK_FAIL);
            uTexLocArray.emplace_back(loc);
        }
        uMVPMatLoc = getUniformLocation("mvp");
        FkAssert(uMVPMatLoc >= 0, FK_FAIL);
        uViewportMatLoc = getUniformLocation("viewportMat");
        uTransMatrixLoc = getUniformLocation("uTransMatrix");
        FkAssert(uTransMatrixLoc >= 0, FK_FAIL);
        uColsLoc = getUniformLocation("colsX");
        uRowsLoc = getUniformLocation("rowsY");
        uWidthLoc = getUniformLocation("width");
        uHeightLoc = getUniformLocation("height");
        uSliceWidthLoc = getUniformLocation("sliceWidth");
        uSliceHeightLoc = getUniformLocation("sliceHeight");
        aCoordinateLoc = getAttribLocation("aTextureCoord");
        FkAssert(aCoordinateLoc >= 0, FK_FAIL);
    }
    return ret;
}

void FkGraphicMatProgram::clear() {
    for (auto itr = values.rbegin(); itr != values.rend(); ++itr) {
        auto it = *itr;
        if (FK_INSTANCE_OF(it, FkVboCompo)) {
            glDisableVertexAttribArray(aPosLoc);
        } else if (FK_INSTANCE_OF(it, FkVboCompo)) {
            glDisableVertexAttribArray(aCoordinateLoc);
        }
    }
    FkGraphicProgram::clear();
}

FkResult FkGraphicMatProgram::addValue(std::shared_ptr<FkComponent> value) {
    if (nullptr == value) {
        return FK_FAIL;
    }
    if (FK_INSTANCE_OF(value, FkTexCompo)) {
        auto pValue = Fk_POINTER_CAST(FkTexCompo, value);
        if (GL_NONE == pValue->tex->tex) {
            glBindTexture(pValue->tex->desc.target, GL_NONE);
        } else {
            glActiveTexture(GL_TEXTURE0 + pValue->index);
            glBindTexture(pValue->tex->desc.target, pValue->tex->tex);
            setUniform1i(uTexLocArray[pValue->index], pValue->index);
        }
    } else if (FK_INSTANCE_OF(value, FkTexArrayCompo)) {
        auto texArrCompo = Fk_POINTER_CAST(FkTexArrayCompo, value);
        if (uColsLoc >= 0) {
            setUniform1i(uColsLoc, texArrCompo->blocks.x);
        }
        if (uRowsLoc >= 0) {
            setUniform1i(uRowsLoc, texArrCompo->blocks.y);
        }
        if (uWidthLoc >= 0) {
            setUniform1i(uWidthLoc, texArrCompo->size.getWidth());
        }
        if (uHeightLoc >= 0) {
            setUniform1i(uHeightLoc, texArrCompo->size.getHeight());
        }
        if (uSliceWidthLoc >= 0) {
            setUniform1i(uSliceWidthLoc, texArrCompo->blockSize.getWidth());
        }
        if (uSliceHeightLoc >= 0) {
            setUniform1i(uSliceHeightLoc, texArrCompo->blockSize.getHeight());
        }
        for (int i = 0; i < texArrCompo->countOfTexture(); ++i) {
            auto compo = std::make_shared<FkTexCompo>((*texArrCompo)[i]);
            compo->index = i;
            addValue(compo);
        }
    } else if (FK_INSTANCE_OF(value, FkVboCompo)) {
        auto pValue = Fk_POINTER_CAST(FkVboCompo, value);
        int offset = 0;
        FkVertexDesc desc;
        FkAssert(FK_OK == pValue->getValueLoc(FkVboCompo::kValueLoc::VERTEX,
                                              offset, desc), FK_FAIL);

        FK_GL_CHECK(glEnableVertexAttribArray(aPosLoc));
        //xy
        FK_GL_CHECK(glVertexAttribPointer(aPosLoc,
                                          desc.countPerVertex, GL_FLOAT, GL_FALSE, 0,
                                          reinterpret_cast<const void *>(offset)));

        offset = 0;
        FkAssert(FK_OK == pValue->getValueLoc(FkVboCompo::kValueLoc::COORDINATE,
                                              offset, desc), FK_FAIL);
        FK_GL_CHECK(glEnableVertexAttribArray(aCoordinateLoc));
        //st
        FK_GL_CHECK(glVertexAttribPointer(aCoordinateLoc,
                                          desc.countPerVertex, GL_FLOAT, GL_FALSE, 0,
                                          reinterpret_cast<const void *>(offset)));
    } else if (FK_INSTANCE_OF(value, FkViewportMatCompo) && uViewportMatLoc >= 0) {
        auto pValue = Fk_POINTER_CAST(FkViewportMatCompo, value);
        glUniformMatrix4fv(uViewportMatLoc, 1, GL_FALSE,
                           reinterpret_cast<const GLfloat *>(pValue->value->get()));
    } else if (nullptr != value && FK_INSTANCE_OF(value, FkTransMatCompo) && uTransMatrixLoc >= 0) {
        auto pValue = Fk_POINTER_CAST(FkTransMatCompo, value);
        glUniformMatrix4fv(uTransMatrixLoc, 1, GL_FALSE,
                           reinterpret_cast<const GLfloat *>(pValue->value->get()));
    } else if (FK_INSTANCE_OF(value, FkMatCompo)) {
        auto pValue = Fk_POINTER_CAST(FkMatCompo, value);
        glUniformMatrix4fv(uMVPMatLoc, 1, GL_FALSE,
                           reinterpret_cast<const GLfloat *>(pValue->value->get()));
    }
    return FkGraphicProgram::addValue(value);
}

std::string FkGraphicMatProgram::getVertex() {
    std::string shader(R"(
        precision highp float;
        attribute vec4 aPosition;
        attribute vec2 aTextureCoord;
        varying vec2 vTextureCoord;
        uniform mat4 mvp;
        uniform mat4 viewportMat;
        uniform mat4 uTransMatrix;
        void main() {
            gl_Position = viewportMat * mvp * uTransMatrix * aPosition;
            vTextureCoord = aTextureCoord;
        })");
    return shader;
}

std::string FkGraphicMatProgram::getFragment() {
    std::string shader(R"(
        precision highp float;
        varying vec2 vTextureCoord;
        uniform sampler2D uTexture[%d];
        uniform int colsX;
        uniform int rowsY;
        uniform int width;
        uniform int height;
        uniform int sliceWidth;
        uniform int sliceHeight;
        void main() {
            float offsetWidth = float(sliceWidth) / float(width);
            float offsetHeight = float(sliceHeight) / float(height);
            int posX = int(vTextureCoord.x / offsetWidth);
            int posY = int(vTextureCoord.y / offsetHeight);
            vec2 coord = vec2(vTextureCoord.x - offsetWidth * float(posX),
                              vTextureCoord.y - offsetHeight * float(posY));
            if (posX + 1 == colsX) {
                coord = vec2(coord.x / (1.0 - float(posX) * offsetWidth), coord.y);
            } else {
                coord = vec2(coord.x / offsetWidth, coord.y);
            }
            if (posY + 1 == rowsY) {
                coord = vec2(coord.x, coord.y / (1.0 - float(posY) * offsetHeight));
            } else {
                coord = vec2(coord.x, coord.y / offsetHeight);
            }
            int index = posY * colsX + posX;
            vec4 color = texture2D(uTexture[index], coord);
//            float count = float(colsX * rowsY);
//            color = vec4(float(index) / count, float(index) / count, float(index) / count, 1.0);
            gl_FragColor = color;
        })");
    size_t size = shader.size() + 10;
    char buf[size];
    memset(buf, 0, size);
    sprintf(buf, shader.c_str(), desc.maxCountOfFragmentTexture);
    shader = std::string(buf);
    return shader;
}

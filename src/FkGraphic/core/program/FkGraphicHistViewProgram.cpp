/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: aliminabc@gmail.com

* CREATE TIME: 2024-07-16 23:26:35
*/

#include "FkGraphicHistViewProgram.h"
#include "FkTexCompo.h"
#include "FkViewportMatCompo.h"
#include "FkTransMatCompo.h"
#include "FkVboCompo.h"
#include "FkTexArrayCompo.h"

FK_IMPL_CLASS_TYPE(FkGraphicHistViewProgram, FkGraphicProgram)

FkGraphicHistViewProgram::FkGraphicHistViewProgram(const FkProgramDescription &desc)
        : FkGraphicProgram(desc) {

}

FkGraphicHistViewProgram::~FkGraphicHistViewProgram() {

}

FkProgramDescription::kType FkGraphicHistViewProgram::type() {
    return FkProgramDescription::kType::HIST_VIEW;
}

FkResult FkGraphicHistViewProgram::create() {
    auto ret = FkGraphicProgram::create();
    if (FK_OK == ret) {
        aPosLoc = getAttribLocation("aPosition");
        FkAssert(aPosLoc >= 0, FK_FAIL);
        uMVPMatLoc = getUniformLocation("mvp");
        FkAssert(uMVPMatLoc >= 0, FK_FAIL);
        uViewportMatLoc = getUniformLocation("viewportMat");
        uTransMatrixLoc = getUniformLocation("uTransMatrix");
        FkAssert(uTransMatrixLoc >= 0, FK_FAIL);
        aCoordinateLoc = getAttribLocation("aTextureCoord");
        FkAssert(aCoordinateLoc >= 0, FK_FAIL);
    }
    return ret;
}

void FkGraphicHistViewProgram::clear() {
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

FkResult FkGraphicHistViewProgram::addValue(std::shared_ptr<FkComponent> value) {
    if (nullptr == value) {
        return FK_FAIL;
    }
    if (FK_INSTANCE_OF(value, FkVboCompo)) {
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

std::string FkGraphicHistViewProgram::getVertex() {
    std::string shader(R"(#version 310 es
        precision highp float;
        in vec4 aPosition;
        in vec2 aTextureCoord;
        out vec2 vTextureCoord;
        uniform mat4 mvp;
        uniform mat4 viewportMat;
        uniform mat4 uTransMatrix;
        void main() {
            gl_Position = viewportMat * mvp * uTransMatrix * aPosition;
            vTextureCoord = aTextureCoord;
        })");
    return shader;
}
//786432
std::string FkGraphicHistViewProgram::getFragment() {
    std::string shader(R"(#version 310 es
        precision highp float;
        precision highp image2D;
        in vec2 vTextureCoord;
        layout (binding = 1) buffer HistBuffer {
            int histData[4][256];
        };
        layout (binding = 2) buffer HistInfoBuffer {
            int maxValue;
        };
        out vec4 fragColor;
        void main() {
            int yValue = int(vTextureCoord.y * float(maxValue));
            int xValue = int(vTextureCoord.x * 255.0);
            ivec3 histValue = ivec3(histData[0][xValue], histData[1][xValue], histData[2][xValue]);
            vec4 color = vec4(0.0, 0.0, 0.0, 1.0);
            if (yValue <= histValue.r) {
                color.r = 1.0;
            } else {
                color.r = 0.0;
            }
            if (yValue <= histValue.g) {
                color.g = 1.0;
            } else {
                color.g = 0.0;
            }
            if (yValue <= histValue.b) {
                color.b = 1.0;
            } else {
                color.b = 0.0;
            }
            if (yValue > histValue.r && yValue > histValue.g && yValue > histValue.b) {
                color = vec4(0.0, 0.0, 0.0, 0.3);
            } else if (yValue <= histValue.r && yValue <= histValue.g && yValue <= histValue.b) {
                color = vec4(0.368627, 0.478431, 0.364706, 1.0);
            }
            fragColor = color;
        })");
    return shader;
}
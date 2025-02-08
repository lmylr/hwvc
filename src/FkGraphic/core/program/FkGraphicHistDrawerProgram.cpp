/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns)

* CREATE TIME: 2024-08-13 22:22:27
*/

#include "FkGraphicHistDrawerProgram.h"
#include "FkTexCompo.h"
#include "FkViewportMatCompo.h"
#include "FkTransMatCompo.h"
#include "FkVboCompo.h"
#include "FkTexArrayCompo.h"

FK_IMPL_CLASS_TYPE(FkGraphicHistDrawerProgram, FkGraphicProgram)

FkGraphicHistDrawerProgram::FkGraphicHistDrawerProgram(const FkProgramDescription &desc)
        : FkGraphicProgram(desc) {

}

FkGraphicHistDrawerProgram::~FkGraphicHistDrawerProgram() {

}

FkProgramDescription::kType FkGraphicHistDrawerProgram::type() {
    return FkProgramDescription::kType::HIST_DRAWER;
}

FkResult FkGraphicHistDrawerProgram::create() {
    auto ret = FkGraphicProgram::create();
    if (FK_OK == ret) {
        aPosLoc = getAttribLocation("aPosition");
        FkAssert(aPosLoc >= 0, FK_FAIL);
    }
    return ret;
}

void FkGraphicHistDrawerProgram::clear() {
    for (auto itr = values.rbegin(); itr != values.rend(); ++itr) {
        auto it = *itr;
        if (FK_INSTANCE_OF(it, FkVboCompo)) {
            glDisableVertexAttribArray(aPosLoc);
        }
    }
    FkGraphicProgram::clear();
}

FkResult FkGraphicHistDrawerProgram::addValue(std::shared_ptr<FkComponent> value) {
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
    }
    return FkGraphicProgram::addValue(value);
}

std::string FkGraphicHistDrawerProgram::getVertex() {
    std::string shader(R"(#version 310 es
        precision highp float;
        in vec4 aPosition;
        out vec2 vTextureCoord;
        void main() {
            gl_Position = aPosition;
            vTextureCoord = (gl_Position.xy + 1.0) / 2.0;
        })");
    return shader;
}

std::string FkGraphicHistDrawerProgram::getFragment() {
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
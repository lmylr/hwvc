/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
* CREATE TIME: 2022-4-26 13:18:24
*/

#include "FkCanvasMatProgram.h"
#include "FkGridSizeCompo.h"
#include "FkBackgroundColorCompo.h"

FK_IMPL_CLASS_TYPE(FkCanvasMatProgram, FkGraphicMatProgram)

FkCanvasMatProgram::FkCanvasMatProgram(const FkProgramDescription &desc) : FkGraphicMatProgram(desc) {

}

FkCanvasMatProgram::~FkCanvasMatProgram() {

}

FkProgramDescription::kType FkCanvasMatProgram::type() {
    return FkProgramDescription::kType::MATRIX_WITH_CANVAS_BACKGROUND;
}

FkResult FkCanvasMatProgram::create() {
    auto ret = FkGraphicMatProgram::create();
    if (FK_OK == ret) {
        uGridSizeXLoc = getUniformLocation("gridSizeX");
        FkAssert(uGridSizeXLoc >= 0, FK_FAIL);
        uGridSizeYLoc = getUniformLocation("gridSizeY");
        FkAssert(uGridSizeYLoc >= 0, FK_FAIL);
        uBackColor0Loc = getUniformLocation("backgroundColor0");
        FkAssert(uBackColor0Loc >= 0, FK_FAIL);
        uIsUseBackColorLoc = getUniformLocation("isUseBackgroundColor");
        FkAssert(uIsUseBackColorLoc >= 0, FK_FAIL);
    }
    return ret;
}

FkResult FkCanvasMatProgram::addValue(std::shared_ptr<FkComponent> value) {
    if (nullptr == value) {
        return FK_FAIL;
    }
    setUniform1i(uIsUseBackColorLoc, 0);
    if (FK_INSTANCE_OF(value, FkGridSizeCompo)) {
        auto pValue = Fk_POINTER_CAST(FkGridSizeCompo, value);
        setUniform1f(uGridSizeXLoc, pValue->vec.x);
        setUniform1f(uGridSizeYLoc, pValue->vec.y);
    } else if (FK_INSTANCE_OF(value, FkBackgroundColorCompo)) {
        auto pValue = Fk_POINTER_CAST(FkBackgroundColorCompo, value);
        setUniform4fv(uBackColor0Loc, 1, pValue->color.fArray());
        setUniform1i(uIsUseBackColorLoc, 1);
    }
    return FkGraphicMatProgram::addValue(value);
}

std::string FkCanvasMatProgram::getVertex() {
    std::string shader(R"(
        precision highp float;
        attribute vec4 aPosition;
        attribute vec2 aTextureCoord;
        varying vec2 vTextureCoord;
        uniform mat4 mvp;
        uniform mat4 uTransMatrix;
        void main() {
            gl_Position = mvp * uTransMatrix * aPosition;
            vTextureCoord = aTextureCoord;
        })");
    return shader;
}

std::string FkCanvasMatProgram::getFragment() {
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
        uniform float gridSizeX;
        uniform float gridSizeY;
        uniform int isUseBackgroundColor;
        uniform vec4 backgroundColor0;
        void main(){
            float offsetWidth = float(sliceWidth) / float(width);
            float offsetHeight = float(sliceHeight) / float(height);
            vec4 back = vec4(1.0, 1.0, 1.0, 1.0);
            if (isUseBackgroundColor == 0) {
                float ix = vTextureCoord.x / gridSizeX;
                float iy = vTextureCoord.y / gridSizeY;
                if (iy / 2.0 - floor(iy / 2.0) >= 0.0 && iy / 2.0 - floor(iy / 2.0) < 0.5) {
                    if (ix / 2.0 - floor(ix / 2.0) >= 0.0 && ix / 2.0 - floor(ix / 2.0) < 0.5) {
                        back = vec4(0.796, 0.796, 0.796, 1.0);
                    }
                } else {
                    if (ix / 2.0 - floor(ix / 2.0) >= 0.5 && ix / 2.0 - floor(ix / 2.0) < 1.0) {
                        back = vec4(0.796, 0.796, 0.796, 1.0);
                    }
                }
            }
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
            if (isUseBackgroundColor == 0) {
                gl_FragColor = mix(color, back, 1.0 - color.a);
            } else {
                gl_FragColor = mix(color, backgroundColor0, 1.0 - color.a);
            }
        })");
    size_t size = shader.size() + 10;
    char buf[size];
    memset(buf, 0, size);
    sprintf(buf, shader.c_str(), desc.maxCountOfFragmentTexture);
    shader = std::string(buf);
    return shader;
}
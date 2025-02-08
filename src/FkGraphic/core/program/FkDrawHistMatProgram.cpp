/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: aliminabc@gmail.com

* CREATE TIME: 2025-02-05 21:42:05
*/

#include "FkDrawHistMatProgram.h"

FK_IMPL_CLASS_TYPE(FkDrawHistMatProgram, FkGraphicMatProgram)

FkDrawHistMatProgram::FkDrawHistMatProgram(const FkProgramDescription &desc)
        : FkGraphicMatProgram(desc) {

}

FkDrawHistMatProgram::~FkDrawHistMatProgram() {

}

FkProgramDescription::kType FkDrawHistMatProgram::type() {
    return FkProgramDescription::kType::DRAW_HIST_MAT;
}

FkResult FkDrawHistMatProgram::create() {
    return FkGraphicMatProgram::create();
}

FkResult FkDrawHistMatProgram::addValue(std::shared_ptr<FkComponent> value) {
    return FkGraphicMatProgram::addValue(value);
}

std::string FkDrawHistMatProgram::getVertex() {
    return FkGraphicMatProgram::getVertex();
}

std::string FkDrawHistMatProgram::getFragment() {
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
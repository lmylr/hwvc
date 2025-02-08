/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns)

* CREATE TIME: 2024-05-25 11:22:25
*/

#include "FkGraphicAndroidMatProgram.h"
#include "FkGLDefinition.h"
#include "FkTexCompo.h"
#include "FkVboCompo.h"
#include "FkMatCompo.h"
#include "FkString.h"
#include "FkTexArrayCompo.h"
#include "FkViewportMatCompo.h"
#include "FkTransMatCompo.h"

FK_IMPL_CLASS_TYPE(FkGraphicAndroidMatProgram, FkGraphicMatProgram)

FkGraphicAndroidMatProgram::FkGraphicAndroidMatProgram(const FkProgramDescription &desc)
        : FkGraphicMatProgram(desc) {

}

FkGraphicAndroidMatProgram::~FkGraphicAndroidMatProgram() {

}

FkProgramDescription::kType FkGraphicAndroidMatProgram::type() {
    return FkProgramDescription::kType::MATRIX_ANDROID;
}

FkResult FkGraphicAndroidMatProgram::create() {
    return FkGraphicMatProgram::create();
}

void FkGraphicAndroidMatProgram::clear() {
    FkGraphicMatProgram::clear();
}

FkResult FkGraphicAndroidMatProgram::addValue(std::shared_ptr<FkComponent> value) {
    return FkGraphicMatProgram::addValue(value);
}

std::string FkGraphicAndroidMatProgram::getVertex() {
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

std::string FkGraphicAndroidMatProgram::getFragment() {
    std::string shader(R"(
        #extension GL_OES_EGL_image_external : require
        precision highp float;
        varying vec2 vTextureCoord;
        uniform samplerExternalOES uTexture[%d];
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
/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: aliminabc@gmail.com

* CREATE TIME: 2024-06-08 18:16:52
*/

#include "FkGraphicColorAdjustProgram.h"
#include "FkColorAdjustCompo.h"

FK_IMPL_CLASS_TYPE(FkGraphicColorAdjustProgram, FkGraphicAndroidMatProgram)

FkGraphicColorAdjustProgram::FkGraphicColorAdjustProgram(const FkProgramDescription &desc) : FkGraphicAndroidMatProgram(desc) {

}

FkGraphicColorAdjustProgram::~FkGraphicColorAdjustProgram() {

}
FkProgramDescription::kType FkGraphicColorAdjustProgram::type() {
    return FkProgramDescription::kType::COLOR_ADJUST;
}

FkResult FkGraphicColorAdjustProgram::create() {
    auto ret = FkGraphicAndroidMatProgram::create();
    if (FK_OK == ret) {
        uBrightnessLoc = getUniformLocation("brightness");
        FkAssert(uBrightnessLoc >= 0, FK_FAIL);
        uContrastLoc = getUniformLocation("contrast");
        FkAssert(uContrastLoc >= 0, FK_FAIL);
        uSaturationLoc = getUniformLocation("saturation");
        FkAssert(uSaturationLoc >= 0, FK_FAIL);
    }
    return ret;
}

void FkGraphicColorAdjustProgram::clear() {
    for (auto itr = values.rbegin(); itr != values.rend(); ++itr) {
    }
    FkGraphicAndroidMatProgram::clear();
}

FkResult FkGraphicColorAdjustProgram::addValue(std::shared_ptr<FkComponent> value) {
    if (nullptr == value) {
        return FK_FAIL;
    }
    if (FK_INSTANCE_OF(value, FkColorAdjustCompo)) {
        auto pValue = Fk_POINTER_CAST(FkColorAdjustCompo, value);
        setUniform1f(uBrightnessLoc, pValue->brightness);
        setUniform1f(uContrastLoc, pValue->contrast);
        setUniform1f(uSaturationLoc, pValue->saturation);
    }
    return FkGraphicAndroidMatProgram::addValue(value);
}

std::string FkGraphicColorAdjustProgram::getVertex() {
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

std::string FkGraphicColorAdjustProgram::getFragment() {
    std::string shader(R"(
        #extension GL_OES_EGL_image_external : require
        precision highp float;
        varying vec2 vTextureCoord;
        uniform samplerExternalOES uTexture[%d];
        const mediump vec3 luminanceWeighting = vec3(0.2125, 0.7154, 0.0721);
        uniform int colsX;
        uniform int rowsY;
        uniform int width;
        uniform int height;
        uniform int sliceWidth;
        uniform int sliceHeight;
        uniform float brightness;
        uniform float contrast;
        uniform float saturation;
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
            vec3 color0 = color.rgb + vec3(brightness);
            vec3 color1 = (color0 - vec3(0.5)) *  contrast + vec3(0.5);
            vec3 color2 = vec3(dot(color1.rgb, luminanceWeighting));
            gl_FragColor = vec4(mix(color2, color1.rgb, saturation), color.w);
        })");
    size_t size = shader.size() + 10;
    char buf[size];
    memset(buf, 0, size);
    sprintf(buf, shader.c_str(), desc.maxCountOfFragmentTexture);
    shader = std::string(buf);
    return shader;
}
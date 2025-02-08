/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: aliminabc@gmail.com

* CREATE TIME: 2024-08-04 22:16:53
*/

#include "FkGraphicAndroidHistCalcProgram.h"
#include "FkTexCompo.h"
#include "FkTexArrayCompo.h"

#define TAG "FkGraphicAndroidHistCalcProgram"

FK_IMPL_CLASS_TYPE(FkGraphicAndroidHistCalcProgram, FkGraphicComputeProgram)

FkGraphicAndroidHistCalcProgram::FkGraphicAndroidHistCalcProgram(const FkProgramDescription &desc)
        : FkGraphicComputeProgram(desc) {

}

FkGraphicAndroidHistCalcProgram::~FkGraphicAndroidHistCalcProgram() {

}

FkProgramDescription::kType FkGraphicAndroidHistCalcProgram::type() {
    return FkProgramDescription::kType::HIST_CALC_ANDROID;
}

FkResult FkGraphicAndroidHistCalcProgram::create() {
    return FkGraphicComputeProgram::create();
}

void FkGraphicAndroidHistCalcProgram::clear() {
    FkGraphicComputeProgram::clear();
}

FkResult FkGraphicAndroidHistCalcProgram::addValue(std::shared_ptr<FkComponent> value) {
    if (nullptr == value) {
        return FK_FAIL;
    }
    if (FK_INSTANCE_OF(value, FkTexCompo)) {
        auto pValue = Fk_POINTER_CAST(FkTexCompo, value);
        if (GL_NONE == pValue->tex->tex) {
            glBindTexture(pValue->tex->desc.target, GL_NONE);
        } else {
            FK_GL_CHECK(glActiveTexture(GL_TEXTURE0 + pValue->index));
            FK_GL_CHECK(glBindTexture(pValue->tex->desc.target, pValue->tex->tex));
            FK_GL_CHECK(setUniform1i(0, pValue->index));
        }
    } else if (FK_INSTANCE_OF(value, FkTexArrayCompo)) {
        auto texArrCompo = Fk_POINTER_CAST(FkTexArrayCompo, value);
        if (uWidthLoc >= 0) {
            FK_GL_CHECK(setUniform1i(uWidthLoc, texArrCompo->size.getWidth()));
        }
        if (uHeightLoc >= 0) {
            FK_GL_CHECK(setUniform1i(uHeightLoc, texArrCompo->size.getHeight()));
        }
        for (int i = 0; i < texArrCompo->countOfTexture(); ++i) {
            auto compo = std::make_shared<FkTexCompo>((*texArrCompo)[i]);
            compo->index = i;
            addValue(compo);
        }
    }
    return FkGraphicComputeProgram::addValue(value);
}

std::string FkGraphicAndroidHistCalcProgram::getVertex() {
    std::string shader(R"(#version 310 es
        #extension GL_OES_EGL_image_external_essl3 : require
        precision highp float;
        precision highp image2D;
        precision highp samplerExternalOES;
        const ivec4 OFFSET = ivec4(0, 1, 2, 3);
        const vec3 GREY_DOT = vec3(0.299, 0.587, 0.114);
        layout (local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
        layout (location = 0) uniform samplerExternalOES inputTexture;
        layout (binding = 1) buffer HistBuffer {
            int histData[4][256];
        };
        layout (binding = 2) buffer HistInfoBuffer {
            int maxValue;
        };
        layout (location = 3) uniform int sliceWidth;
        layout (location = 4) uniform int sliceHeight;
        void main() {
            vec2 texCoord = vec2(gl_GlobalInvocationID.xy);
            vec4 color = texture(inputTexture, vec2(texCoord.x / float(sliceWidth), texCoord.y / float(sliceHeight)));
            color.a = dot(color.rgb, GREY_DOT);
            ivec4 scaled = ivec4(color * 255.0);

            histData[0][scaled.r] = histData[0][scaled.r] + 1;
            histData[1][scaled.g] = histData[1][scaled.g] + 1;
            histData[2][scaled.b] = histData[2][scaled.b] + 1;
            histData[3][scaled.a] = histData[3][scaled.a] + 1;
            maxValue = max(max(histData[0][scaled.r], histData[1][scaled.g]), max(histData[2][scaled.b], maxValue));
//            atomicAdd(histData[0][scaled.r], 1);
//            atomicAdd(histData[1][scaled.g], 1);
//            atomicAdd(histData[2][scaled.b], 1);
//            atomicAdd(histData[3][scaled.a], 1);
//            maxValue = atomicMax(histData[0][scaled.r], maxValue);
//            maxValue = atomicMax(histData[1][scaled.g], maxValue);
//            maxValue = atomicMax(histData[2][scaled.b], maxValue);
        })");
    return shader;
}
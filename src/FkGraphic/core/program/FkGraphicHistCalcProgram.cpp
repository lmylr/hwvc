/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns)

* CREATE TIME: 2024-07-18 23:04:48
*/

#include "FkGraphicHistCalcProgram.h"
#include "FkVboCompo.h"
#include "FkTexCompo.h"
#include "FkTexArrayCompo.h"
#include "FkString.h"

FK_IMPL_CLASS_TYPE(FkGraphicHistCalcProgram, FkGraphicComputeProgram)

FkGraphicHistCalcProgram::FkGraphicHistCalcProgram(const FkProgramDescription &desc)
        : FkGraphicComputeProgram(desc) {

}

FkGraphicHistCalcProgram::~FkGraphicHistCalcProgram() {

}

FkProgramDescription::kType FkGraphicHistCalcProgram::type() {
    return FkProgramDescription::kType::HIST_CALC;
}

FkResult FkGraphicHistCalcProgram::create() {
    auto ret = FkGraphicComputeProgram::create();
    if (FK_OK == ret) {
        for (int i = 0; i < desc.maxCountOfFragmentTexture; ++i) {
            FkString key("uTexture[");
            key.append(i);
            key.append(']');
            auto loc = getUniformLocation(key.str());
            FkAssert(loc >= 0, FK_FAIL);
            uTexLocArray.emplace_back(loc);
        }
    }
    return ret;
}

void FkGraphicHistCalcProgram::clear() {
    FkGraphicComputeProgram::clear();
}

FkResult FkGraphicHistCalcProgram::addValue(std::shared_ptr<FkComponent> value) {
    if (nullptr == value) {
        return FK_FAIL;
    }
    if (FK_INSTANCE_OF(value, FkTexCompo)) {
        auto pValue = Fk_POINTER_CAST(FkTexCompo, value);
        if (GL_NONE == pValue->tex->tex) {
            FK_GL_CHECK(glBindTexture(pValue->tex->desc.target, GL_NONE));
        } else {
            FK_GL_CHECK(glActiveTexture(GL_TEXTURE0 + pValue->index));
            FK_GL_CHECK(glBindTexture(pValue->tex->desc.target, pValue->tex->tex));
            FK_GL_CHECK(setUniform1i(uTexLocArray[pValue->index], pValue->index));
        }
    } else if (FK_INSTANCE_OF(value, FkTexArrayCompo)) {
        auto texArrCompo = Fk_POINTER_CAST(FkTexArrayCompo, value);
        int32_t texCount = texArrCompo->countOfTexture();
        if (uSliceWidthLoc >= 0) {
            FK_GL_CHECK(setUniform1i(uSliceWidthLoc, texArrCompo->blockSize.getWidth()));
        }
        if (uSliceHeightLoc >= 0) {
            FK_GL_CHECK(setUniform1i(uSliceHeightLoc, texArrCompo->blockSize.getHeight()));
        }
        for (int i = 0; i < texCount; ++i) {
            auto compo = std::make_shared<FkTexCompo>((*texArrCompo)[i]);
            compo->index = i;
            addValue(compo);
        }
    }
    return FkGraphicComputeProgram::addValue(value);
}

std::string FkGraphicHistCalcProgram::getVertex() {
    std::string shader(R"(#version 310 es
        #extension GL_EXT_gpu_shader5 : require
        precision highp float;
        precision highp image2D;
        precision highp sampler2D;
        const vec3 GREY_DOT = vec3(0.299, 0.587, 0.114);
        layout (local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
        uniform sampler2D uTexture[%d];
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
            int index = int(gl_GlobalInvocationID.z);
            vec2 coord = vec2(texCoord.x / float(sliceWidth), texCoord.y / float(sliceHeight));

            vec4 color = texture(uTexture[index], coord);
            color.a = dot(color.rgb, GREY_DOT);
            ivec4 scaled = ivec4(color * 255.0);

            histData[0][scaled.r] = histData[0][scaled.r] + 1;
            histData[1][scaled.g] = histData[1][scaled.g] + 1;
            histData[2][scaled.b] = histData[2][scaled.b] + 1;
            histData[3][scaled.a] = histData[3][scaled.a] + 1;
            maxValue = max(max(histData[0][scaled.r], histData[1][scaled.g]), max(histData[2][scaled.b], maxValue));
        })");
    size_t size = shader.size() + 10;
    char buf[size];
    memset(buf, 0, size);
    sprintf(buf, shader.c_str(), desc.maxCountOfFragmentTexture);
    shader = std::string(buf);
    return shader;
}
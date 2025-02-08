/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: aliminabc@gmail.com

* CREATE TIME: 2024-08-01 23:13:33
*/

#include "FkGraphicResetImageProgram.h"

FK_IMPL_CLASS_TYPE(FkGraphicResetImageProgram, FkGraphicComputeProgram)

FkGraphicResetImageProgram::FkGraphicResetImageProgram(const FkProgramDescription &desc)
        : FkGraphicComputeProgram(desc) {

}

FkGraphicResetImageProgram::~FkGraphicResetImageProgram() {

}

FkProgramDescription::kType FkGraphicResetImageProgram::type() {
    return FkProgramDescription::kType::RESET_IMAGE;
}

std::string FkGraphicResetImageProgram::getVertex() {
    std::string shader(R"(#version 310 es
        precision highp float;
        layout (local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
        layout (binding = 1) buffer HistBuffer {
            int histData[];
        };
        void main() {
            ivec2 texCoord = ivec2(gl_GlobalInvocationID.xy);
            histData[texCoord.x] = 0;
        })");
    return shader;
}
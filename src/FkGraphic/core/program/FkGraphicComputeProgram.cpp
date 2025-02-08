/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: aliminabc@gmail.com

* CREATE TIME: 2024-07-24 23:28:47
*/

#include "FkGraphicComputeProgram.h"

FK_IMPL_CLASS_TYPE(FkGraphicComputeProgram, FkGraphicProgram)

FkGraphicComputeProgram::FkGraphicComputeProgram(const FkProgramDescription &desc)
        : FkGraphicProgram(desc) {

}

FkGraphicComputeProgram::~FkGraphicComputeProgram() {

}

FkResult FkGraphicComputeProgram::create() {
    desc.type = type();
    program = glCreateProgram();
    FkAssert(GL_NONE != program, GL_NONE);
    std::string vertex = getVertex();
    std::string fragment = getFragment();
    GLuint vertexShader = createShader(GL_COMPUTE_SHADER, vertex);
    FkAssert(GL_NONE != vertexShader, GL_NONE);
    glAttachShader(program, vertexShader);
    FK_GL_CHECK(glLinkProgram(program));
    FkAssert(GL_NO_ERROR == glGetError(), FK_FAIL);
    return FK_OK;
}

std::string FkGraphicComputeProgram::getFragment() {
    return "";
}
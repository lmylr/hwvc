/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns)

* CREATE TIME: 2024-06-23 20:51:33
*/

#include "FkGraphicYUVProgram.h"
#include "FkVboCompo.h"
#include "FkTexArrayCompo.h"

FK_IMPL_CLASS_TYPE(FkGraphicYUVProgram, FkGraphicProgram)

FkGraphicYUVProgram::FkGraphicYUVProgram(const FkProgramDescription &desc)
        : FkGraphicProgram(desc) {
}

FkGraphicYUVProgram::~FkGraphicYUVProgram() {

}

FkProgramDescription::kType FkGraphicYUVProgram::type() {
    return FkProgramDescription::kType::YV12;
}

FkResult FkGraphicYUVProgram::create() {
    auto ret = FkGraphicProgram::create();
    if (FK_OK == ret) {
        aPosLoc = getAttribLocation("aPosition");
        FkAssert(aPosLoc >= 0, FK_FAIL);
        aCoordinateLoc = getAttribLocation("aTextureCoord");
        FkAssert(aCoordinateLoc >= 0, FK_FAIL);
        auto loc = getUniformLocation("uTexture0");
        FkAssert(loc >= 0, FK_FAIL);
        uTexLocArray.emplace_back(loc);
        loc = getUniformLocation("uTexture1");
        FkAssert(loc >= 0, FK_FAIL);
        uTexLocArray.emplace_back(loc);
        loc = getUniformLocation("uTexture2");
        if (loc >= 0) {
            uTexLocArray.emplace_back(loc);
        }
    }
    return ret;
}

void FkGraphicYUVProgram::clear() {
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

FkResult FkGraphicYUVProgram::addValue(std::shared_ptr<FkComponent> value) {
    if (nullptr == value) {
        return FK_FAIL;
    }
    if (FK_INSTANCE_OF(value, FkTexArrayCompo)) {
        auto texArrCompo = Fk_POINTER_CAST(FkTexArrayCompo, value);
        for (int i = 0; i < uTexLocArray.size(); ++i) {
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(texArrCompo->textures[i]->desc.target, texArrCompo->textures[i]->tex);
            setUniform1i(uTexLocArray[i], i);
        }
    } else if (FK_INSTANCE_OF(value, FkVboCompo)) {
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
    }
    return FkGraphicProgram::addValue(value);
}

std::string FkGraphicYUVProgram::getVertex() {
    std::string shader(R"(
        precision mediump float;
        attribute vec4 aPosition;
        attribute vec2 aTextureCoord;
        varying vec2 vTextureCoord;
        void main(void) {
            gl_Position = aPosition;
            vTextureCoord = aTextureCoord;
        })");
    return shader;
}

// Default
// (1, 1, 1,
//  0, -0.337633, 1.732446,
//  1.370705, -0.6908001, 0);
// BT.601
// (1, 1, 1,
//  0, -0.39465, 2.03211,
//  1.13983, -0.58060, 0);
// BT.709
// (1, 1, 1,
//  0, -0.21482, 2.12798,
//  1.28033, -0.38057, 0);
std::string FkGraphicYUVProgram::getFragment() {
    std::string shader(R"(
        precision mediump float;
        varying vec2 vTextureCoord;
        uniform sampler2D uTexture0;//Y
        uniform sampler2D uTexture1;//UV
        const mat3 YUV2RGB = mat3(1, 1, 1,
                                 0, -0.337633, 1.732446,
                                 1.370705, -0.6908001, 0);
        void main(void) {
            vec3 yuv;
            vec3 rgb;
            yuv.x = texture2D(uTexture0, vTextureCoord).r;
            yuv.y = texture2D(uTexture1, vTextureCoord).r - 0.5;
            yuv.z = texture2D(uTexture1, vTextureCoord).a - 0.5;
            rgb = YUV2RGB * yuv;
            gl_FragColor = vec4(rgb, 1);
        })");
    return shader;
}
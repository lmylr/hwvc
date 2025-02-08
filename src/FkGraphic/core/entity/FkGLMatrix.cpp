/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: aliminabc@gmail.com

* CREATE TIME: 2024-06-19 22:29:30
*/

#include "FkGLMatrix.h"
#include "ext/matrix_clip_space.hpp"
#include "ext.hpp"

FK_IMPL_CLASS_TYPE(FkGLMatrix, FkMatrix)

FkGLMatrix::FkGLMatrix()
        : FkMatrix(), mat4(glm::mat4(1.0f)){

}

FkGLMatrix::FkGLMatrix(const FkGLMatrix &o) : FkMatrix(o), mat4(o.mat4) {

}

FkGLMatrix::~FkGLMatrix() {

}

void FkGLMatrix::reset() {
    mat4 = glm::mat4(1.0f);
}

void FkGLMatrix::setViewSize(int32_t width, int32_t height) {
}

void FkGLMatrix::lookAt(FkFloatVec3 cameraPosition, FkFloatVec3 shootVec, FkFloatVec3 headVec) {
}

void FkGLMatrix::setScale(FkFloatVec3 value) {
    mat4 = glm::scale(mat4, glm::vec3(value.x, value.y, value.z));
}

void FkGLMatrix::setRotation(FkRational _radian) {
    mat4 = glm::rotate(mat4, -_radian.num * 1.0f / _radian.den, glm::vec3(0.0f, 0.0f, 1.0f));
}

void FkGLMatrix::setTranslate(FkFloatVec3 value) {
    mat4 = glm::translate(mat4, glm::vec3(value.x, value.y, value.z));
}

const void *FkGLMatrix::get() {
    return glm::value_ptr(mat4);
}

FkDoubleVec2 FkGLMatrix::calcVec2(FkDoubleVec2 &vec2) {
    glm::vec4 vec(vec2.x, vec2.y, 0, 1.0f);
    vec = vec * mat4;
    return FkDoubleVec2(vec.x, vec.y);
}

bool FkGLMatrix::isZero() {
    return mat4[0][0] == 0 && mat4[1][1] == 0 && mat4[2][2] == 0 && mat4[3][3] == 0;
}

void FkGLMatrix::set(int32_t row, int32_t col, float value) {
    mat4[row][col] = value;
}

float FkGLMatrix::get(int32_t row, int32_t col) {
    return mat4[row][col];
}

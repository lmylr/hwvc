/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#include "FkMVPMatrix.h"
#include "ext/matrix_clip_space.hpp"
#include "ext.hpp"

FK_IMPL_CLASS_TYPE(FkMVPMatrix, FkGLMatrix)

FkMVPMatrix::FkMVPMatrix(kProjType type)
        : FkGLMatrix(), type(type), view(glm::mat4(1.0f)), proj(glm::mat4(1.0f)) {

}

FkMVPMatrix::FkMVPMatrix(const FkMVPMatrix &o) : FkGLMatrix(o), type(o.type),
                                                 proj(o.proj), view(o.view) {

}

FkMVPMatrix::~FkMVPMatrix() {

}

void FkMVPMatrix::setViewSize(int32_t width, int32_t height) {
    proj = glm::ortho(-width / 2.0f, width / 2.0f,
                      -height / 2.0f, height / 2.0f,
                      0.1f, 100.0f);
}

void FkMVPMatrix::lookAt(FkFloatVec3 cameraPosition, FkFloatVec3 shootVec, FkFloatVec3 headVec) {
    view = glm::lookAt(
            glm::vec3(cameraPosition.x, cameraPosition.y, cameraPosition.z), // Camera is at (0,0,3), in World Space
            glm::vec3(shootVec.x, shootVec.y, shootVec.z), // and looks at the origin
            glm::vec3(headVec.x, headVec.y, headVec.z)  // Head is up (set to 0,-1,0 to look upside-down)
    );
}

void FkMVPMatrix::set(int32_t row, int32_t col, float value) {

}

float FkMVPMatrix::get(int32_t row, int32_t col) {
    return 0.0f;
}

const void *FkMVPMatrix::get() {
    if (proj != glm::mat4(1.0f) && view != glm::mat4(1.0f)) {
        tmp = proj * view * mat4;
        return glm::value_ptr(tmp);
    }
    return FkGLMatrix::get();
}

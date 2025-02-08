/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#ifndef FK_GRAPHIC_FKMVPMATRIX_H
#define FK_GRAPHIC_FKMVPMATRIX_H

#include "FkGLMatrix.h"
#include "glm.hpp"

FK_SUPER_CLASS(FkMVPMatrix, FkGLMatrix) {
FK_DEF_CLASS_TYPE_FUNC(FkMVPMatrix)

public:
    FK_ENUM kProjType : uint32_t {
        ORTHO = 0,
        PERSPECTIVE,
    };
public:
    FkMVPMatrix(kProjType type);

    FkMVPMatrix(const FkMVPMatrix &o);

    virtual ~FkMVPMatrix();

    virtual void setViewSize(int32_t width, int32_t height) override;

    virtual void lookAt(FkFloatVec3 cameraPosition,
                        FkFloatVec3 shootVec,
                        FkFloatVec3 headVec) override;

    virtual void set(int32_t row, int32_t col, float value) override;

    virtual float get(int32_t row, int32_t col) override;

    virtual const void *get() override;

private:
    kProjType type;
    glm::mat4 proj;
    glm::mat4 view;
    glm::mat4 tmp;
};

#endif //FK_GRAPHIC_FKMVPMATRIX_H
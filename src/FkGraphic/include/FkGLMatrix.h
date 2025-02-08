/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns)

* CREATE TIME: 2024-06-19 22:29:30
*/

#ifndef FK_GRAPHIC_FKGLMATRIX_H
#define FK_GRAPHIC_FKGLMATRIX_H

#include "FkMatrix.h"
#include "glm.hpp"

FK_SUPER_CLASS(FkGLMatrix, FkMatrix) {
FK_DEF_CLASS_TYPE_FUNC(FkGLMatrix)

public:
    FkGLMatrix();

    FkGLMatrix(const FkGLMatrix &o);

    virtual ~FkGLMatrix();

    virtual void reset() override;

    virtual void setViewSize(int32_t width, int32_t height) override;

    virtual void lookAt(FkFloatVec3 cameraPosition,
                        FkFloatVec3 shootVec,
                        FkFloatVec3 headVec) override;

    virtual void setScale(FkFloatVec3 value) override;

    virtual void setRotation(FkRational _radian) override;

    virtual void setTranslate(FkFloatVec3 value) override;

    virtual FkDoubleVec2 calcVec2(FkDoubleVec2 &vec2) override;

    virtual const void *get() override;

    virtual bool isZero() override;

    virtual void set(int32_t row, int32_t col, float value) override;

    virtual float get(int32_t row, int32_t col) override;

protected:
    glm::mat4 mat4;
};

#endif //FK_GRAPHIC_FKGLMATRIX_H
/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns)

* CREATE TIME: 2024-06-23 15:01:14
*/

#include "FkBufferedImageSource.h"
#include "FkGLDefinition.h"
#include "FkMath.h"
#include "FkGLMatrix.h"

FK_IMPL_CLASS_TYPE(FkBufferedImageSource, FkAbsImageSource)

FkBufferedImageSource::FkBufferedImageSource(const BufferDesc desc)
        : FkAbsImageSource(), desc(desc), matrix(std::make_shared<FkGLMatrix>()) {
}

FkBufferedImageSource::~FkBufferedImageSource() {

}

FkResult FkBufferedImageSource::onCreate(int32_t arg0, int64_t arg1, const std::string &arg2) {
    matrix->reset();
    if (desc.orientation == FkEncodedOrigin::kRightTop) {
        matrix->setRotation({FkMath::PI_R.num * 3, FkMath::PI_R.den * 2});
    } else if (desc.orientation == FkEncodedOrigin::kLeftBottom)  {
        matrix->setRotation({FkMath::PI_R.num, FkMath::PI_R.den * 2});
    } else if (desc.orientation == FkEncodedOrigin::kRightBottom)  {
        matrix->setRotation({FkMath::PI_R.num * 3, FkMath::PI_R.den * 2});
        matrix->setScale(FkFloatVec3(-1.0f, 1.0f, 1.0f));
    } else if (desc.orientation == FkEncodedOrigin::kLeftTop)  {
        matrix->setRotation({FkMath::PI_R.num, FkMath::PI_R.den * 2});
        matrix->setScale(FkFloatVec3(-1.0f, 1.0f, 1.0f));
    }
    return FK_OK;
}

FkResult FkBufferedImageSource::onDestroy() {
    return FK_NOT_SUPPORT;
}

FkResult FkBufferedImageSource::onRender(int32_t arg0, int64_t arg1, const std::string &arg2) {
    return FK_NOT_SUPPORT;
}

FkSize FkBufferedImageSource::getSize() {
    return desc.size;
}

std::shared_ptr<FkMatrix> FkBufferedImageSource::getTransformMatrix() {
    return matrix;
}

int64_t FkBufferedImageSource::getTimestampInNS() {
    return 0;
}

FkTexDescription FkBufferedImageSource::getTexDescription() {
    FkTexDescription _desc;
    _desc.target = GL_TEXTURE_2D;
    return _desc;
}

std::shared_ptr<FkBitmap> FkBufferedImageSource::toBitmap() {
    return nullptr;
}
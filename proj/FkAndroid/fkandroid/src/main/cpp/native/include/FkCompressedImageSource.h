/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns)

* CREATE TIME: 2024/6/16.
*/

#ifndef ANDROID_FKCOMPRESSEDIMAGESOURCE_H
#define ANDROID_FKCOMPRESSEDIMAGESOURCE_H

#include "FkBufferedImageSource.h"
#include "FkJavaRuntime.h"
#include "FkJniGlobalRef.h"
#include "FkFloatVec2.h"

FK_SUPER_CLASS(FkCompressedImageSource, FkBufferedImageSource) {
FK_DEF_CLASS_TYPE_FUNC(FkCompressedImageSource)

public:
    FkCompressedImageSource(jobject javaSource, const std::shared_ptr<FkBitmap> &bmp, const FkEncodedOrigin orientation);

    FkCompressedImageSource(const FkCompressedImageSource &o) = delete;

    virtual ~FkCompressedImageSource();

    virtual FkResult onCreate(int32_t arg0, int64_t arg1, const std::string &arg2) override;

    virtual FkResult onDestroy() override;

    virtual FkResult onRender(int32_t arg0, int64_t arg1, const std::string &arg2) override;

    virtual FkSize getSize() override;

    virtual std::shared_ptr<FkMatrix> getTransformMatrix() override;

    virtual int64_t getTimestampInNS() override;

    virtual FkTexDescription getTexDescription() override;

    virtual std::shared_ptr<FkBitmap> toBitmap() override;

private:
    std::unique_ptr<FkJniGlobalRef> javaSource = nullptr;
    jmethodID midOnCreate = nullptr;
    jmethodID midOnDestroy = nullptr;
    jmethodID midOnRender = nullptr;
    jmethodID midGetTimestamp = nullptr;
    int64_t lastRenderTime = -1;
    std::shared_ptr<FkBitmap> bmp = nullptr;
};


#endif //ANDROID_FKCOMPRESSEDIMAGESOURCE_H

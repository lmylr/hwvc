/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: aliminabc@gmail.com

* CREATE TIME: 2024-06-23 21:17:59
*/

#ifndef FK_GRAPHIC_FKYV12IMAGESOURCE_H
#define FK_GRAPHIC_FKYV12IMAGESOURCE_H

#include "FkBufferedImageSource.h"
#include "FkBuffer.h"
#include "FkGraphicYUVProgram.h"

FK_SUPER_CLASS(FkYUV420SPImageSource, FkBufferedImageSource) {
FK_DEF_CLASS_TYPE_FUNC(FkYUV420SPImageSource)

public:
    FkYUV420SPImageSource(const BufferDesc desc);

    FkYUV420SPImageSource(const FkYUV420SPImageSource &o) = delete;

    virtual ~FkYUV420SPImageSource();

    virtual FkResult onCreate(int32_t arg0, int64_t arg1, const std::string &arg2) override;

    virtual FkResult onDestroy() override;

    virtual FkResult onRender(int32_t arg0, int64_t arg1, const std::string &arg2) override;

    virtual FkSize getSize() override;

    virtual std::shared_ptr<FkMatrix> getTransformMatrix() override;

    virtual int64_t getTimestampInNS() override;

    virtual FkTexDescription getTexDescription() override;

    virtual std::shared_ptr<FkBitmap> toBitmap() override;

private:
    std::vector<std::shared_ptr<FkBuffer>> planes;
};

#endif //FK_GRAPHIC_FKYV12IMAGESOURCE_H
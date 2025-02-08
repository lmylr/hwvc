/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: aliminabc@gmail.com

* CREATE TIME: 2024-06-23 15:01:14
*/

#ifndef FK_GRAPHIC_FKBUFFEREDIMAGESOURCE_H
#define FK_GRAPHIC_FKBUFFEREDIMAGESOURCE_H

#include "FkAbsImageSource.h"
#include "FkBuffer.h"
#include "FkBitmap.h"
#include "FkFloatVec2.h"

FK_SUPER_CLASS(FkBufferedImageSource, FkAbsImageSource) {
FK_DEF_CLASS_TYPE_FUNC(FkBufferedImageSource)

public:
    typedef struct _BufferDesc {
        std::vector<std::shared_ptr<FkBuffer>> planes;
        FkSize size = {0, 0};
        FkEncodedOrigin orientation = FkEncodedOrigin::kDefault;
    } BufferDesc;

public:
    FkBufferedImageSource(const BufferDesc desc);

    FkBufferedImageSource(const FkBufferedImageSource &o) = delete;

    virtual ~FkBufferedImageSource();

    virtual FkResult onCreate(int32_t arg0, int64_t arg1, const std::string &arg2) override;

    virtual FkResult onDestroy() override;

    virtual FkResult onRender(int32_t arg0, int64_t arg1, const std::string &arg2) override;

    virtual FkSize getSize() override;

    virtual std::shared_ptr<FkMatrix> getTransformMatrix() override;

    virtual int64_t getTimestampInNS() override;

    virtual FkTexDescription getTexDescription() override;

    virtual std::shared_ptr<FkBitmap> toBitmap() override;

protected:
    BufferDesc desc;
    std::shared_ptr<FkMatrix> matrix = nullptr;
};

#endif //FK_GRAPHIC_FKBUFFEREDIMAGESOURCE_H
/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#ifndef FK_IMAGE_FKBITMAP_H
#define FK_IMAGE_FKBITMAP_H

#include "FkObject.h"
#include "FkColor.h"
#include "FkSize.h"
#include "FkBuffer.h"
#include "FkImage.h"
#include "FkBitmapDefinition.h"
#include "include/core/SkBitmap.h"

FK_SUPER_CLASS(FkBitmap, FkObject) {
FK_DEF_CLASS_TYPE_FUNC(FkBitmap)

public:
    static std::shared_ptr<FkBitmap> create(const int32_t width, const int32_t height);

    static std::shared_ptr<FkBitmap> from(std::string &file);

    static std::shared_ptr<FkBitmap> from(const std::shared_ptr<FkBuffer> &compressedBuf, bool isCopy = false);

    static std::shared_ptr<FkBitmap> fromYUV(const std::vector<std::shared_ptr<FkBuffer>> &planes, FkSize size, FkEncodedOrigin orientation, bool isCopy = false);

    static FkResult write(std::string file, FkImage::Format fmt, std::shared_ptr<FkBuffer> buf, FkSize size, int quality);

private:
    FkBitmap(const int32_t width, const int32_t height);

    FkBitmap(const sk_sp<SkData> &data);

    FkBitmap(const std::vector<std::shared_ptr<FkBuffer>> &planes, FkSize size, FkEncodedOrigin orientation, bool isCopy);

    FkBitmap(const FkBitmap &o);

    void _setEncodedOrigin(int32_t skEncodedOrigin);

public:
    virtual ~FkBitmap();

    int getWidth();

    int getHeight();

    /**
     * 改变HwBitmap大小和格式，用于内存复用
     */
    FkResult resize(int width, int height, FkColor::kFormat fmt);

    /**
     * 获取指向图片像素内存的指针
     */
    uint8_t *getPixels();

    /**
     * 获取图片占用的内存大小
     */
    uint64_t getByteSize();

    /**
     * 获取图像编码角度，即图片相对于原方向的旋转角度，正数表示顺时针
     * @return FkEncodedOrigin
     */
    FkEncodedOrigin getEncodedOrigin();

    bool isSwappedWH();

    FkResult write(const std::string &file, FkImage::Format fmt, int quality);

//    AlRational getRotation();

//    void dump();

private:
    std::shared_ptr<SkBitmap> bmp = nullptr;
    FkEncodedOrigin encodedOrigin = FkEncodedOrigin::kDefault;
};

#endif //FK_IMAGE_FKBITMAP_H
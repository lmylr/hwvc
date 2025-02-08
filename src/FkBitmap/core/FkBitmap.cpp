/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#include "FkBitmap.h"
#include "include/core/SkData.h"
#include "include/core/SkRefCnt.h"
#include "include/codec/SkCodec.h"
#include "include/core/SkImage.h"
#include "include/core/SkImageEncoder.h"
#include "include/core/SkPixelRef.h"
#include "libyuv.h"

FK_IMPL_CLASS_TYPE(FkBitmap, FkObject)

std::shared_ptr<FkBitmap> FkBitmap::create(const int32_t width, const int32_t height) {
    auto bmp =  std::shared_ptr<FkBitmap>(new FkBitmap(width, height));
    if (bmp->bmp == nullptr) {
        return nullptr;
    }
    return bmp;
}

std::shared_ptr<FkBitmap> FkBitmap::from(std::string &file) {
    auto bmp =  std::shared_ptr<FkBitmap>(new FkBitmap(SkData::MakeFromFileName(file.c_str())));
    if (bmp->bmp == nullptr) {
        return nullptr;
    }
    return bmp;
}

std::shared_ptr<FkBitmap> FkBitmap::from(const std::shared_ptr<FkBuffer> &compressedBuf, bool isCopy) {
    sk_sp<SkData> data = nullptr;
    if (isCopy) {
        data = SkData::MakeFromMalloc(compressedBuf->data(), compressedBuf->capacity());
    } else {
        data = SkData::MakeWithoutCopy(compressedBuf->data(), compressedBuf->capacity());
    }
    auto bmp =  std::shared_ptr<FkBitmap>(new FkBitmap(data));
    if (bmp->bmp == nullptr) {
        return nullptr;
    }
    return bmp;
}

std::shared_ptr<FkBitmap> FkBitmap::fromYUV(const std::vector<std::shared_ptr<FkBuffer>> &planes,
                                            FkSize size, FkEncodedOrigin orientation, bool isCopy) {
    auto bmp =  std::shared_ptr<FkBitmap>(new FkBitmap(planes, size, orientation, isCopy));
    if (bmp->bmp == nullptr) {
        return nullptr;
    }
    return bmp;
}

FkResult FkBitmap::write(std::string file, FkImage::Format fmt, std::shared_ptr<FkBuffer> buf,
                         FkSize size, int quality) {
    sk_sp<SkPixelRef> pixelRef = sk_make_sp<SkPixelRef>(size.getWidth(),
                                                        size.getHeight(),
                                                        buf->data(),
                                                        size.getWidth() * 4);
    auto bmp = std::make_shared<SkBitmap>();
    bmp->setInfo(SkImageInfo::Make(pixelRef->width(), pixelRef->height(),kRGBA_8888_SkColorType,kOpaque_SkAlphaType), pixelRef->rowBytes());
    bmp->setPixelRef(pixelRef, 0, 0);
    SkEncodedImageFormat skFmt;
    switch (fmt) {
        case FkImage::Format::kBMP: {
            skFmt = SkEncodedImageFormat::kBMP;
            break;
        }
        case FkImage::Format::kJPEG: {
            skFmt = SkEncodedImageFormat::kJPEG;
            break;
        }
        case FkImage::Format::kPNG: {
            skFmt = SkEncodedImageFormat::kPNG;
            break;
        }
        case FkImage::Format::kWEBP: {
            skFmt = SkEncodedImageFormat::kWEBP;
            break;
        }
        default:
            skFmt = SkEncodedImageFormat::kJPEG;
    }
    auto encodedData = SkEncodeBitmap(*bmp, skFmt, quality);
    if (encodedData != nullptr) {
        FILE *f = fopen(file.c_str(), "wb");
        if (f) {
            fwrite(encodedData->data(), 1, encodedData->size(), f);
            fclose(f);
            return FK_OK;
        }
        return FK_IO_FAIL;
    }
    return FK_FAIL;
}

FkBitmap::FkBitmap(const int32_t width, const int32_t height) : FkObject() {
    bmp = std::make_shared<SkBitmap>();
    bmp->setInfo(SkImageInfo::Make(width, height, kRGBA_8888_SkColorType,kOpaque_SkAlphaType));
    if (!bmp->tryAllocPixels()) {
        FkLogI(FK_DEF_TAG, "Can not alloc pixels memory with size.");
        bmp = nullptr;
        return;
    }
}

FkBitmap::FkBitmap(const sk_sp<SkData> &data) : FkObject() {
    std::unique_ptr<SkCodec> codec = SkCodec::MakeFromData(data);
    if (!codec) {
        FkLogI(FK_DEF_TAG, "Can not find codec for SkData");
        return;
    }
    SkImageInfo info = codec->getInfo().makeColorType(kN32_SkColorType)
            .makeAlphaType(SkAlphaType::kPremul_SkAlphaType);
    bmp = std::make_shared<SkBitmap>();
    if (!bmp->tryAllocPixels(info)) {
        FkLogI(FK_DEF_TAG, "Can not alloc pixels memory with encoded data.");
        return;
    }
    if (SkCodec::kSuccess != codec->getPixels(info, bmp->getPixels(), bmp->rowBytes())) {
        FkLogI(FK_DEF_TAG, "Can not read pixels.");
    }
    _setEncodedOrigin(codec->getOrigin());
}

FkBitmap::FkBitmap(const std::vector<std::shared_ptr<FkBuffer>> &planes, FkSize size,
                   FkEncodedOrigin orientation, bool isCopy) {
    FkSize rotatedSize = size;
    libyuv::RotationMode mode = libyuv::RotationMode::kRotate0;
    switch (orientation) {
        case FkEncodedOrigin::kRightTop:
        case FkEncodedOrigin::kLeftTop: {
            mode = libyuv::RotationMode::kRotate90;
            rotatedSize.swap();
            break;
        }
        case FkEncodedOrigin::kLeftBottom:
        case FkEncodedOrigin::kRightBottom: {
            mode = libyuv::RotationMode::kRotate270;
            rotatedSize.swap();
            break;
        }
    }
    bmp = std::make_shared<SkBitmap>();
    bmp->setInfo(SkImageInfo::Make(rotatedSize.getWidth(), rotatedSize.getHeight(), kRGBA_8888_SkColorType,kOpaque_SkAlphaType));
    if (!bmp->tryAllocPixels()) {
        FkLogI(FK_DEF_TAG, "Can not alloc pixels memory with planes.");
        bmp = nullptr;
        return;
    }
    auto buf = FkBuffer::alloc(size.getWidth() * size.getHeight() * 4);
    auto dst = static_cast<uint8_t *>(bmp->getPixels());
    if (orientation == FkEncodedOrigin::kRightBottom || orientation == FkEncodedOrigin::kLeftTop) {
        libyuv::NV12ToABGR(planes[0]->data(), size.getWidth(),
                           planes[1]->data(), size.getWidth(),
                           dst, size.getWidth() * 4,
                           size.getWidth(), size.getHeight());
        libyuv::ARGBRotate(dst, size.getWidth() * 4,
                           buf->data(), bmp->width() * 4,
                           size.getWidth(), size.getHeight(), mode);
        libyuv::ARGBMirror(buf->data(), bmp->width() * 4,
                           dst, bmp->width() * 4,
                           bmp->width(), bmp->height());
    } else {
        libyuv::NV12ToABGR(planes[0]->data(), size.getWidth(),
                           planes[1]->data(), size.getWidth(),
                           buf->data(), size.getWidth() * 4,
                           size.getWidth(), size.getHeight());
        libyuv::ARGBRotate(buf->data(), size.getWidth() * 4,
                           dst, bmp->width() * 4,
                           size.getWidth(), size.getHeight(), mode);
    }
}

FkBitmap::FkBitmap(const FkBitmap &o) : FkObject(o) {

}

void FkBitmap::_setEncodedOrigin(int32_t skEncodedOrigin) {
    encodedOrigin = static_cast<FkEncodedOrigin>(skEncodedOrigin);
    FkLogI(FK_DEF_TAG, "orientation: %d", encodedOrigin);
}

FkBitmap::~FkBitmap() {
    bmp = nullptr;
}

int FkBitmap::getWidth() {
    return bmp->width();
}

int FkBitmap::getHeight() {
    return bmp->height();
}

FkResult FkBitmap::resize(int width, int height, FkColor::kFormat fmt) {
    return FK_FAIL;
}

uint8_t *FkBitmap::getPixels() {
    return (uint8_t *) bmp->getPixels();

}

uint64_t FkBitmap::getByteSize() {
    return bmp->computeByteSize();
}

FkEncodedOrigin FkBitmap::getEncodedOrigin() {
    return encodedOrigin;
}

bool FkBitmap::isSwappedWH() {
    return encodedOrigin >= FkEncodedOrigin::kLeftTop && encodedOrigin <= FkEncodedOrigin::kLeftBottom;
}

FkResult FkBitmap::write(const std::string &file, FkImage::Format fmt, int quality) {
    SkEncodedImageFormat skFmt;
    switch (fmt) {
        case FkImage::Format::kBMP: {
            skFmt = SkEncodedImageFormat::kBMP;
            break;
        }
        case FkImage::Format::kJPEG: {
            skFmt = SkEncodedImageFormat::kJPEG;
            break;
        }
        case FkImage::Format::kPNG: {
            skFmt = SkEncodedImageFormat::kPNG;
            break;
        }
        case FkImage::Format::kWEBP: {
            skFmt = SkEncodedImageFormat::kWEBP;
            break;
        }
        default:
            skFmt = SkEncodedImageFormat::kJPEG;
    }
    auto encodedData = SkEncodeBitmap(*bmp, skFmt, quality);
    if (encodedData != nullptr) {
        FILE *f = fopen(file.c_str(), "wb");
        if (f) {
            fwrite(encodedData->data(), 1, encodedData->size(), f);
            fclose(f);
            return FK_OK;
        }
        return FK_IO_FAIL;
    }
    return FK_FAIL;
}

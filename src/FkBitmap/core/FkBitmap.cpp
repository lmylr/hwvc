/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
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

#define TAG "FkBitmap"

static constexpr skcms_Matrix3x3 kDCI_P3_D65 = {{{0.515102f, 0.291965f, 0.157153f},
                                                 {0.241182f, 0.692236f, 0.0665819f},
                                                 {-0.00104941f, 0.0418818f, 0.784378f},
                                                }};

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
        FkLogI(TAG, "Can not alloc pixels memory with size.");
        bmp = nullptr;
        return;
    }
}

FkBitmap::FkBitmap(const sk_sp<SkData> &data) : FkObject() {
    std::unique_ptr<SkCodec> codec = SkCodec::MakeFromData(data);
    if (!codec) {
        FkLogI(TAG, "Can not find codec for SkData");
        return;
    }
    auto info = codec->getInfo();
    bmp = std::make_shared<SkBitmap>();
    if (!bmp->tryAllocPixels(info)) {
        FkLogI(TAG, "Can not alloc pixels memory with encoded data.");
        return;
    }
    FkLogI(TAG, "bytesPerPixel=%d, byteSize=%d", bmp->bytesPerPixel(), bmp->computeByteSize());
    SkImageInfo dstInfo = info.makeColorSpace(nullptr).makeAlphaType(kUnpremul_SkAlphaType);
    if (SkCodec::kSuccess != codec->getPixels(dstInfo, bmp->getPixels(), bmp->rowBytes())) {
        FkLogI(TAG, "Can not read pixels.");
    }
    _setEncodedOrigin(codec->getOrigin());
    FkLogI(TAG, "ICCProfile: %s", getColorProfileDescription().c_str());
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
        FkLogI(TAG, "Can not alloc pixels memory with planes.");
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
    FkLogI(TAG, "orientation: %d", encodedOrigin);
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

static bool nearly_equal(float x, float y) {
    static constexpr float kTolerance = 1.0f / (1 << 11);
    return ::fabsf(x - y) <= kTolerance;
}

static bool nearly_equal(const skcms_TransferFunction& u,
                         const skcms_TransferFunction& v) {
    return nearly_equal(u.g, v.g)
           && nearly_equal(u.a, v.a)
           && nearly_equal(u.b, v.b)
           && nearly_equal(u.c, v.c)
           && nearly_equal(u.d, v.d)
           && nearly_equal(u.e, v.e)
           && nearly_equal(u.f, v.f);
}

static bool nearly_equal(const skcms_Matrix3x3& u, const skcms_Matrix3x3& v) {
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            if (!nearly_equal(u.vals[r][c], v.vals[r][c])) {
                return false;
            }
        }
    }
    return true;
}

std::string FkBitmap::getColorProfileDescription() {
    if (bmp == nullptr) {
        return {};
    }
    auto colorSpace = bmp->colorSpace();
    if (colorSpace == nullptr) {
        return {};
    }
    skcms_TransferFunction fn;
    skcms_Matrix3x3 toXYZD50;
    colorSpace->invTransferFn(&fn);
    colorSpace->toXYZD50(&toXYZD50);
    bool srgb_xfer = nearly_equal(fn, SkNamedTransferFn::kSRGB);
    bool srgb_gamut = nearly_equal(toXYZD50, SkNamedGamut::kSRGB);
    if (srgb_xfer && srgb_gamut) {
        return "sRGB";
    }
    bool line_xfer = nearly_equal(fn, SkNamedTransferFn::kLinear);
    if (line_xfer && srgb_gamut) {
        return "Linear Transfer with sRGB Gamut";
    }
    bool twoDotTwo = nearly_equal(fn, SkNamedTransferFn::k2Dot2);
    if (twoDotTwo && srgb_gamut) {
        return "2.2 Transfer with sRGB Gamut";
    }
    if (twoDotTwo && nearly_equal(toXYZD50, SkNamedGamut::kAdobeRGB)) {
        return "AdobeRGB";
    }
    bool display_p3 = nearly_equal(toXYZD50, SkNamedGamut::kDisplayP3);
    if (srgb_xfer || line_xfer) {
        if (srgb_xfer && display_p3) {
            return "sRGB Transfer with Display P3 Gamut";
        }
        if (line_xfer && display_p3) {
            return "Linear Transfer with Display P3 Gamut";
        }
        bool rec2020 = nearly_equal(toXYZD50, SkNamedGamut::kRec2020);
        if (srgb_xfer && rec2020) {
            return "sRGB Transfer with Rec-BT-2020 Gamut";
        }
        if (line_xfer && rec2020) {
            return "Linear Transfer with Rec-BT-2020 Gamut";
        }
    } else {
        if (display_p3) {
            return "Unknown Transfer with Display P3 Gamut";
        }
//        FkLogI(TAG, "0[%f, %f, %f]", toXYZD50.vals[0][0], toXYZD50.vals[0][1], toXYZD50.vals[0][2]);
//        FkLogI(TAG, "1[%f, %f, %f]", toXYZD50.vals[1][0], toXYZD50.vals[1][1], toXYZD50.vals[1][2]);
//        FkLogI(TAG, "2[%f, %f, %f]", toXYZD50.vals[2][0], toXYZD50.vals[2][1], toXYZD50.vals[2][2]);
        bool rec2020 = nearly_equal(toXYZD50, SkNamedGamut::kRec2020);
        if (rec2020) {
            return "Unknown Transfer with Rec-BT-2020 Gamut";
        }
    }
    return {};
}

/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns)

* CREATE TIME: 2024-05-19 23:38:55
*/

#ifndef FK_GRAPHIC_FKABSIMAGESOURCE_H
#define FK_GRAPHIC_FKABSIMAGESOURCE_H

#include "FkObject.h"
#include "FkSize.h"
#include "FkMatrix.h"
#include "FkGraphicTexture.h"
#include "FkBitmap.h"

FK_SUPER_CLASS(FkAbsImageSource, FkObject) {
FK_DEF_CLASS_TYPE_FUNC(FkAbsImageSource)

public:
    FkAbsImageSource();

    FkAbsImageSource(const FkAbsImageSource &o);

    virtual ~FkAbsImageSource();

    virtual FkResult onCreate(int32_t arg0, int64_t arg1, const std::string &arg2) = 0;

    virtual FkResult onDestroy() = 0;

    virtual FkResult onRender(int32_t arg0, int64_t arg1, const std::string &arg2) = 0;

    virtual FkSize getSize() = 0;

    virtual std::shared_ptr<FkMatrix> getTransformMatrix() = 0;

    virtual int64_t getTimestampInNS() = 0;

    virtual FkTexDescription getTexDescription() = 0;

    virtual std::shared_ptr<FkBitmap> toBitmap() = 0;

};

#endif //FK_GRAPHIC_FKABSIMAGESOURCE_H
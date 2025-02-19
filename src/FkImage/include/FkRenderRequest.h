/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#ifndef FK_GRAPHIC_FKRENDERREQUEST_H
#define FK_GRAPHIC_FKRENDERREQUEST_H

#include "FkGraphicEntity.h"
#include "FkGraphicLayer.h"
#include "FkBuffer.h"
#include "FkSize.h"

FK_SUPER_CLASS(FkRenderRequest, FkGraphicEntity) {
FK_DEF_CLASS_TYPE_FUNC(FkRenderRequest)

public:
    typedef struct _Strategy {
        bool isOnce = false;
        FkSize outSize = FkSize(0, 0);
        kScaleType scaleType = kScaleType::DEFAULT;
        std::shared_ptr<FkBuffer> buf = nullptr;
        std::function<void()> doneFunc = nullptr;
    } Strategy;

public:
    FkRenderRequest();

    FkRenderRequest(const FkRenderRequest &o);

    virtual ~FkRenderRequest();

    std::shared_ptr<FkGraphicLayer> getCanvas();

public:
    std::vector<std::shared_ptr<FkGraphicLayer>> layers;
    Strategy strategy;
};

#endif //FK_GRAPHIC_FKRENDERREQUEST_H
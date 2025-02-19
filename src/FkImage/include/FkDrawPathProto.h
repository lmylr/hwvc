/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
* CREATE TIME: 2022-5-6 13:07:48
*/

#ifndef FK_IMAGE_FKDRAWPATHPROTO_H
#define FK_IMAGE_FKDRAWPATHPROTO_H

#include "FkProtocol.h"
#include "FkDoubleVec2.h"
#include "FkPaint.h"

FK_SUPER_CLASS(FkDrawPathProto, FkProtocol) {
FK_DEF_CLASS_TYPE_FUNC(FkDrawPathProto)

public:
    FkDrawPathProto(FkID layerId, FkDoubleVec2 &point);

    FkDrawPathProto(const FkDrawPathProto &o);

    virtual ~FkDrawPathProto();

public:
    FkID layerId;
    FkDoubleVec2 point;
    std::shared_ptr<FkPaint> paint = nullptr;
    bool isFinish = false;
    float scaleOfSensitivity = 1.0f;
};

#endif //FK_IMAGE_FKDRAWPATHPROTO_H
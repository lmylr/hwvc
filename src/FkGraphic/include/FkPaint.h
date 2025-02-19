/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns)

* CREATE TIME: 2022-05-13 18:17:58
*/

#ifndef FK_GRAPHIC_FKPAINT_H
#define FK_GRAPHIC_FKPAINT_H

#include "FkObject.h"

FK_SUPER_CLASS(FkPaint, FkObject) {
FK_DEF_CLASS_TYPE_FUNC(FkPaint)

public:
    FkPaint();

    FkPaint(const FkPaint &o);

    virtual ~FkPaint();

public:
    int32_t strokeWidth = 0;
    int32_t color = 0;
};

#endif //FK_GRAPHIC_FKPAINT_H
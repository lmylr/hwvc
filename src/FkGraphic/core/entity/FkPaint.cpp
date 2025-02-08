/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns)

* CREATE TIME: 2022-05-13 18:17:58
*/

#include "FkPaint.h"

FK_IMPL_CLASS_TYPE(FkPaint, FkObject)

FkPaint::FkPaint() : FkObject() {

}

FkPaint::FkPaint(const FkPaint &o)
        : FkObject(o),
          strokeWidth(o.strokeWidth),
          color(o.color) {

}

FkPaint::~FkPaint() {

}

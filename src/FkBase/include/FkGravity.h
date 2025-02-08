/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: aliminabc@gmail.com

* CREATE TIME: 2025-02-05 22:49:47
*/

#ifndef FK_BASE_FKGRAVITY_H
#define FK_BASE_FKGRAVITY_H

#include "FkObject.h"

FK_SUPER_CLASS(FkGravity, FkObject) {
FK_DEF_CLASS_TYPE_FUNC(FkGravity)

public:
    const static int AXIS_SPECIFIED;
    const static int AXIS_Y_SHIFT;
    const static int AXIS_X_SHIFT;
    const static int CENTER_VERTICAL;
    const static int CENTER_HORIZONTAL;
    const static int CENTER;
    const static int LEFT;
    const static int TOP;
    const static int RIGHT;
    const static int BOTTOM;

public:
    FkGravity();

    FkGravity(const FkGravity &o);

    virtual ~FkGravity();
};

#endif //FK_BASE_FKGRAVITY_H
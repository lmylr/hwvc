/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#ifndef FKANDROID_FKBITMAPDEFINITION_H
#define FKANDROID_FKBITMAPDEFINITION_H

#include "FkDefinition.h"

FK_ENUM FkEncodedOrigin : int {
    kTopLeft     = 1, // Default
    kTopRight    = 2, // Reflected across y-axis
    kBottomRight = 3, // Rotated 180
    kBottomLeft  = 4, // Reflected across x-axis
    kLeftTop     = 5, // Reflected across x-axis, Rotated 90 CCW. Swapped width height
    kRightTop    = 6, // Rotated 90 CW. Swapped width height
    kRightBottom = 7, // Reflected across x-axis, Rotated 90 CW. Swapped width height
    kLeftBottom  = 8, // Rotated 90 CCW. Swapped width height
    kDefault     = kTopLeft,
    kCenterVertical = 9,
    kCenterHorizontal = 10,
    kCenter = 11,
    kLeft = 12,
    kTop = 13,
    kRight = 14,
    kBottom = 15,
};

#endif //FKANDROID_FKBITMAPDEFINITION_H

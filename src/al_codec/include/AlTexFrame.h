/*
 * Copyright (c) 2018-present, aliminabc@gmail.com.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#ifndef HWVC_ANDROID_ALTEXFRAME_H
#define HWVC_ANDROID_ALTEXFRAME_H

#include "HwVideoFrame.h"
#include "HwAbsTexture.h"

al_class AlTexFrame al_extend HwVideoFrame {
public:
    AlTexFrame(HwAbsTexture *tex);

    virtual ~AlTexFrame();

    HwAbsTexture *tex();

private:
    AlTexFrame(const AlTexFrame &o);

private:
    HwAbsTexture *_tex = nullptr;
};


#endif //HWVC_ANDROID_ALTEXFRAME_H

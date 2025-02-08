/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#ifndef FK_GRAPHIC_FKGLDEFINITION_H
#define FK_GRAPHIC_FKGLDEFINITION_H

//#include <GLES2/gl2.h>
//#include <GLES2/gl2ext.h>
//#include <GLES3/gl3.h>
#include <GLES3/gl31.h>
#include <GLES3/gl3ext.h>
#include <EGL/egl.h>
#include "assert.h"

#define FK_DEF_GL_TAG "FilmKilnsGL"
#if defined(__FK_DEBUG__)
#define FK_GL_CHECK(statement)                                        \
    do {                                                              \
        statement;                                                    \
        GLenum e = glGetError();                                      \
        if (e != GL_NO_ERROR) {                                       \
            std::string msg = "Unknown";                              \
            switch (e) {                                              \
                case GL_INVALID_OPERATION:                            \
                    msg = "GL_INVALID_OPERATION";                     \
                    break;                                            \
            }                                                         \
            FkLogE(FK_DEF_GL_TAG, "Get error %s(%i, 0x%x) at %s",     \
                   msg.c_str(), e, e, #statement);                    \
            assert(e == GL_NO_ERROR);                                 \
        }                                                             \
    } while(0)
#else
#define FK_GL_CHECK(statement) statement
#endif

#define FK_GL_VER_2 0x0004
#define FK_GL_VER_3 0x00000040

#ifndef __gles2_gl2ext_h_
#define GL_TEXTURE_EXTERNAL_OES           0x8D65
#define GL_TEXTURE_BORDER_COLOR_EXT       0x1004
#define GL_CLAMP_TO_BORDER_EXT            0x812D
#define GL_TEXTURE_BORDER_COLOR_OES       0x1004
#define GL_CLAMP_TO_BORDER_OES            0x812D
#endif

#endif //FK_GRAPHIC_FKGLDEFINITION_H
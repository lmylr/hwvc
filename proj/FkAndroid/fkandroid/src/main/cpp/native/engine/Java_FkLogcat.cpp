/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#include "jni.h"
#include "FkJniDefinition.h"
#include "FkLogcat.h"

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void Java_com_alimin_fk_utils_FkLogcat_nativeLog
        (JNIEnv *env, jobject that, jint type, jstring tag, jstring msg) {
    FkJniStringUTF8 _tag(env, tag);
    FkJniStringUTF8 _msg(env, msg);
    switch (type) {
        case 0: {
            FkLogcat::v(_tag.c_str(), _msg.c_str());
            break;
        }
        case 1: {
            FkLogcat::d(_tag.c_str(), _msg.c_str());
            break;
        }
        case 2: {
            FkLogcat::i(_tag.c_str(), _msg.c_str());
            break;
        }
        case 3: {
            FkLogcat::w(_tag.c_str(), _msg.c_str());
            break;
        }
        case 4: {
            FkLogcat::e(_tag.c_str(), _msg.c_str());
            break;
        }
    }
}

#ifdef __cplusplus
}
#endif



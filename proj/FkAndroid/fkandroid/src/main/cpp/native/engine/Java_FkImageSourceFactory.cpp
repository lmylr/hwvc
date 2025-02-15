/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns)

* CREATE TIME: 2025/2/13.
*/

#include "jni.h"
#include "FkJavaRuntime.h"
#include "FkAbsImageSource.h"
#include "FkInstanceHolder.h"
#include "FkSurfaceTextureSource.h"
#include "FkCompressedImageSource.h"
#include "FkYUV420SPImageSource.h"

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jlong JNICALL Java_com_alimin_fk_source_FkImageSourceNativeFactory_00024Companion_nativeCreateSurface
        (JNIEnv *env, jobject that, jobject instance) {
    std::shared_ptr<FkAbsImageSource> source = std::make_shared<FkSurfaceTextureSource>(instance);
    return FkInstanceHolder::getInstance().put(source);
}

JNIEXPORT void JNICALL Java_com_alimin_fk_source_FkImageSourceNativeFactory_00024Companion_nativeDestroy
        (JNIEnv *env, jobject that, jlong handle) {
    FkInstanceHolder::getInstance().release(handle);
}


#ifdef __cplusplus
}
#endif
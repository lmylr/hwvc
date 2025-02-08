/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns)

* CREATE TIME: 2024/6/16
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

JNIEXPORT jlong JNICALL Java_com_alimin_fk_core_FkAbsImageSource_00024Companion_nativeCreateSurface
        (JNIEnv *env, jobject that, jobject instance) {
    std::shared_ptr<FkAbsImageSource> source = std::make_shared<FkSurfaceTextureSource>(instance);
    return FkInstanceHolder::getInstance().put(source);
}

JNIEXPORT jlong JNICALL Java_com_alimin_fk_core_FkAbsImageSource_00024Companion_nativeCreateCompressed
        (JNIEnv *env, jobject that, jobject instance, jobject buf, jint orientation) {
    auto address = env->GetDirectBufferAddress(buf);
    auto _buf = FkBuffer::wrap((uint8_t *) address, env->GetDirectBufferCapacity(buf));
    auto source = std::make_shared<FkCompressedImageSource>(instance, FkBitmap::from(_buf), (FkEncodedOrigin) orientation);
    return FkInstanceHolder::getInstance().put(std::dynamic_pointer_cast<FkAbsImageSource>(source));
}

JNIEXPORT jlong JNICALL Java_com_alimin_fk_core_FkAbsImageSource_00024Companion_nativeCreateYUV420
        (JNIEnv *env, jobject that, jobject instance,
         jobjectArray planes, jint width, jint height, jint orientation) {
    auto len = env->GetArrayLength(planes);
    if (planes && len >= 2) {
        std::vector<std::shared_ptr<FkBuffer>> _planes(len);
        for (int i = 0; i < len; ++i) {
            jobject buf = env->GetObjectArrayElement(planes, i);
            auto capacity = env->GetDirectBufferCapacity(buf);
            auto address = env->GetDirectBufferAddress(buf);
            _planes[i] = FkBuffer::alloc(capacity + 1);
            _planes[i]->put(address, capacity);
            env->DeleteLocalRef(buf);
        }
        FkBufferedImageSource::BufferDesc desc = {_planes, {width, height}, (FkEncodedOrigin) orientation};
        auto source = std::make_shared<FkYUV420SPImageSource>(desc);
        return FkInstanceHolder::getInstance().put(std::dynamic_pointer_cast<FkAbsImageSource>(source));
    }
    return 0;
}

JNIEXPORT void JNICALL Java_com_alimin_fk_core_FkAbsImageSource_00024Companion_nativeDestroy
        (JNIEnv *env, jobject that, jlong handle) {
    FkInstanceHolder::getInstance().release(handle);
}


#ifdef __cplusplus
}
#endif

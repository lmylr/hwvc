/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns)

* CREATE TIME: 2024/6/16.
*/

#include "FkCompressedImageSource.h"
#include "FkJniStringUTF8.h"
#include "FkGLDefinition.h"
#include "FkGLMatrix.h"
#include "FkBitmap.h"

FK_IMPL_CLASS_TYPE(FkCompressedImageSource, FkBufferedImageSource)

FkCompressedImageSource::FkCompressedImageSource(jobject javaSource,
                                                 const std::shared_ptr<FkBitmap> &bmp,
                                                 const FkEncodedOrigin orientation)
        : FkBufferedImageSource({{FkBuffer::wrap(bmp->getPixels(), bmp->getByteSize())},
                                 {bmp->getWidth(), bmp->getHeight()}, orientation}), bmp(bmp) {
    this->javaSource = std::make_unique<FkJniGlobalRef>(javaSource);
    JNIEnv *env = nullptr;
    if (FkJavaRuntime::getInstance().findEnv2(&env)) {
        jclass clazz = env->GetObjectClass(javaSource);
        midOnCreate = env->GetMethodID(clazz, "onCreate", "(IJLjava/lang/String;)I");
        midOnDestroy = env->GetMethodID(clazz, "onDestroy", "()I");
        midOnRender = env->GetMethodID(clazz, "onRender", "(IJLjava/lang/String;)I");
        midGetTimestamp = env->GetMethodID(clazz, "getTimestampInNS", "()J");
    }
}

FkCompressedImageSource::~FkCompressedImageSource() {
    this->javaSource = nullptr;
}

FkResult FkCompressedImageSource::onCreate(int32_t arg0, int64_t arg1, const std::string &arg2) {
    auto ret = FkBufferedImageSource::onCreate(arg0, arg1, arg2);
    glBindTexture(GL_TEXTURE_2D, arg0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, desc.size.getWidth(), desc.size.getHeight(), 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, desc.planes[0]->data());
    glBindTexture(GL_TEXTURE_2D, GL_NONE);
    JNIEnv *env = nullptr;
    if (FkJavaRuntime::getInstance().findEnv2(&env)) {
        FkJniStringUTF8 str(arg2);
        ret = env->CallIntMethod(javaSource->obj(), midOnCreate, arg0, arg1, str.str());
    }
    return ret;
}

FkResult FkCompressedImageSource::onDestroy() {
    FkBufferedImageSource::onDestroy();
    JNIEnv *env = nullptr;
    if (FkJavaRuntime::getInstance().findEnv2(&env)) {
        return env->CallIntMethod(javaSource->obj(), midOnDestroy);
    }
    return FK_INVALID_STATE;
}

FkResult FkCompressedImageSource::onRender(int32_t arg0, int64_t arg1, const std::string &arg2) {
    FkBufferedImageSource::onRender(arg0, arg1, arg2);
    auto timestamp = getTimestampInNS();
    if (timestamp == lastRenderTime) {
        return FK_OK;
    }
    lastRenderTime = timestamp;
    JNIEnv *env = nullptr;
    if (FkJavaRuntime::getInstance().findEnv2(&env)) {
        FkJniStringUTF8 str(arg2);
        return env->CallIntMethod(javaSource->obj(), midOnRender, arg0, arg1, str.str());
    }
    return FK_INVALID_STATE;
}

FkSize FkCompressedImageSource::getSize() {
    return FkBufferedImageSource::getSize();
}

std::shared_ptr<FkMatrix> FkCompressedImageSource::getTransformMatrix() {
    return matrix;
}

int64_t FkCompressedImageSource::getTimestampInNS() {
    JNIEnv *env = nullptr;
    if (FkJavaRuntime::getInstance().findEnv2(&env)) {
        jlong result = env->CallLongMethod(javaSource->obj(), midGetTimestamp);
        return result;
    }
    return 0;
}

FkTexDescription FkCompressedImageSource::getTexDescription() {
    FkTexDescription desc;
    desc.target = GL_TEXTURE_2D;
    return desc;
}

std::shared_ptr<FkBitmap> FkCompressedImageSource::toBitmap() {
    return bmp;
}

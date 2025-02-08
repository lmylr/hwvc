/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: Alimin
* CREATE TIME: 2022-4-23 14:15:54
*/

#ifndef FKANDROID_FKSURFACETEXTURESOURCE_H
#define FKANDROID_FKSURFACETEXTURESOURCE_H

#include "FkAbsImageSource.h"
#include "FkJavaRuntime.h"
#include "FkJniGlobalRef.h"
#include "FkMatrix.h"

FK_SUPER_CLASS(FkSurfaceTextureSource, FkAbsImageSource) {
FK_DEF_CLASS_TYPE_FUNC(FkSurfaceTextureSource)

public:
    FkSurfaceTextureSource(jobject javaSource);

    FkSurfaceTextureSource(const FkSurfaceTextureSource &o) = delete;

    virtual ~FkSurfaceTextureSource();

    virtual FkResult onCreate(int32_t arg0, int64_t arg1, const std::string &arg2) override;

    virtual FkResult onDestroy() override;

    virtual FkResult onRender(int32_t arg0, int64_t arg1, const std::string &arg2) override;

    virtual FkSize getSize() override;

    virtual std::shared_ptr<FkMatrix> getTransformMatrix() override;

    virtual int64_t getTimestampInNS() override;

    virtual FkTexDescription getTexDescription() override;

    virtual std::shared_ptr<FkBitmap> toBitmap() override;

private:
    void _updateTransformMatrix(JNIEnv *env);

private:
    std::unique_ptr<FkJniGlobalRef> javaSource = nullptr;
    jmethodID midGetSize = nullptr;
    jmethodID midOnCreate = nullptr;
    jmethodID midOnDestroy = nullptr;
    jmethodID midOnRender = nullptr;
    jmethodID midGetMatrix = nullptr;
    jmethodID midGetTimestamp = nullptr;
    std::shared_ptr<FkMatrix> matrix = nullptr;
    int64_t lastRenderReqId = -1;
};

#endif //FKANDROID_FKSURFACETEXTURESOURCE_H
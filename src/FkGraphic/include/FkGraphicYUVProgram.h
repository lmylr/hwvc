/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: aliminabc@gmail.com

* CREATE TIME: 2024-06-23 20:51:33
*/

#ifndef FK_GRAPHIC_FKGRAPHICYV12PROGRAM_H
#define FK_GRAPHIC_FKGRAPHICYV12PROGRAM_H

#include "FkGraphicProgram.h"


/// YUV Format
/// +------------------------------------------+
/// |    YUV420P(3Plane)   |  YUV420SP(2Plane)  |
/// +------------------------------------------+
/// | YU12/I420   |  YV12  |   NV12   |  NV21  |
/// +------------------------------------------+
/// |    Y+U+V    | Y+V+U  |   Y+UV   |  Y+VU  |
/// +------------------------------------------+
FK_SUPER_CLASS(FkGraphicYUVProgram, FkGraphicProgram) {
FK_DEF_CLASS_TYPE_FUNC(FkGraphicYUVProgram)

public:
    FkGraphicYUVProgram(const FkProgramDescription &desc);

    FkGraphicYUVProgram(const FkGraphicYUVProgram &o) = delete;

    virtual ~FkGraphicYUVProgram();

    virtual FkProgramDescription::kType type() override;

    virtual FkResult create() override;

    virtual std::string getVertex() override;

    virtual std::string getFragment() override;

    virtual void clear() override;

    virtual FkResult addValue(std::shared_ptr<FkComponent> value) override;

private:
    int32_t aPosLoc = -1;
    int32_t aCoordinateLoc = -1;
    std::vector<int32_t> uTexLocArray;
};

#endif //FK_GRAPHIC_FKGRAPHICYV12PROGRAM_H
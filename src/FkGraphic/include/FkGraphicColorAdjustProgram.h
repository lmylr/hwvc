/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: aliminabc@gmail.com

* CREATE TIME: 2024-06-08 18:16:52
*/

#ifndef FK_GRAPHIC_FKGRAPHICSATURATIONPROGRAM_H
#define FK_GRAPHIC_FKGRAPHICSATURATIONPROGRAM_H

#include "FkGraphicAndroidMatProgram.h"

FK_SUPER_CLASS(FkGraphicColorAdjustProgram, FkGraphicAndroidMatProgram) {
FK_DEF_CLASS_TYPE_FUNC(FkGraphicColorAdjustProgram)

public:
    FkGraphicColorAdjustProgram(const FkProgramDescription &desc);

    FkGraphicColorAdjustProgram(const FkGraphicColorAdjustProgram &o) = delete;

    virtual ~FkGraphicColorAdjustProgram();

    virtual FkProgramDescription::kType type() override;

    virtual FkResult create() override;

    virtual void clear() override;

    virtual FkResult addValue(std::shared_ptr<FkComponent> value) override;

public:
    virtual std::string getVertex() override;

    virtual std::string getFragment() override;

private:
    int32_t uBrightnessLoc = -1;
    int32_t uContrastLoc = -1;
    int32_t uSaturationLoc = -1;
};

#endif //FK_GRAPHIC_FKGRAPHICSATURATIONPROGRAM_H
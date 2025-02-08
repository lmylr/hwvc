/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns)

* CREATE TIME: 2024-08-04 22:16:54
*/

#ifndef FK_GRAPHIC_FKGRAPHICANDROIDHISTCALCPROGRAM_H
#define FK_GRAPHIC_FKGRAPHICANDROIDHISTCALCPROGRAM_H

#include "FkGraphicComputeProgram.h"

FK_SUPER_CLASS(FkGraphicAndroidHistCalcProgram, FkGraphicComputeProgram) {
FK_DEF_CLASS_TYPE_FUNC(FkGraphicAndroidHistCalcProgram)

public:
    FkGraphicAndroidHistCalcProgram(const FkProgramDescription &desc);

    FkGraphicAndroidHistCalcProgram(const FkGraphicAndroidHistCalcProgram &o) = delete;

    virtual ~FkGraphicAndroidHistCalcProgram();

    virtual FkProgramDescription::kType type() override;

    virtual FkResult create() override;

    virtual std::string getVertex() override;

    virtual void clear() override;

    virtual FkResult addValue(std::shared_ptr<FkComponent> value) override;

private:
    int32_t uWidthLoc = 3;
    int32_t uHeightLoc = 4;
};

#endif //FK_GRAPHIC_FKGRAPHICANDROIDHISTCALCPROGRAM_H
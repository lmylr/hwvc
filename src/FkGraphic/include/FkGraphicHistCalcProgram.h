/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns)

* CREATE TIME: 2024-07-18 23:04:48
*/

#ifndef FK_GRAPHIC_FKGRAPHICHISTCALCPROGRAM_H
#define FK_GRAPHIC_FKGRAPHICHISTCALCPROGRAM_H

#include "FkGraphicComputeProgram.h"

FK_SUPER_CLASS(FkGraphicHistCalcProgram, FkGraphicComputeProgram) {
FK_DEF_CLASS_TYPE_FUNC(FkGraphicHistCalcProgram)

public:
    FkGraphicHistCalcProgram(const FkProgramDescription &desc);

    FkGraphicHistCalcProgram(const FkGraphicHistCalcProgram &o) = delete;

    virtual ~FkGraphicHistCalcProgram();

    virtual FkProgramDescription::kType type() override;

    virtual FkResult create() override;

    virtual std::string getVertex() override;

    virtual void clear() override;

    virtual FkResult addValue(std::shared_ptr<FkComponent> value) override;

private:
    std::vector<int32_t> uTexLocArray;
    int32_t uSliceWidthLoc = 3;
    int32_t uSliceHeightLoc = 4;
};

#endif //FK_GRAPHIC_FKGRAPHICHISTCALCPROGRAM_H
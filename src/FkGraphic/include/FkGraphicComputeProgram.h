/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns)

* CREATE TIME: 2024-07-24 23:28:48
*/

#ifndef FK_GRAPHIC_FKGRAPHICCOMPUTEPROGRAM_H
#define FK_GRAPHIC_FKGRAPHICCOMPUTEPROGRAM_H

#include "FkGraphicProgram.h"

FK_SUPER_CLASS(FkGraphicComputeProgram, FkGraphicProgram) {
FK_DEF_CLASS_TYPE_FUNC(FkGraphicComputeProgram)

public:
    FkGraphicComputeProgram(const FkProgramDescription &desc);

    FkGraphicComputeProgram(const FkGraphicComputeProgram &o) = delete;

    virtual ~FkGraphicComputeProgram();

    virtual FkResult create() override;

private:
    std::string getFragment() override;
};

#endif //FK_GRAPHIC_FKGRAPHICCOMPUTEPROGRAM_H
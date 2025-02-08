/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: aliminabc@gmail.com

* CREATE TIME: 2025-02-05 21:42:05
*/

#ifndef FK_GRAPHIC_FKDRAWHISTMATPROGRAM_H
#define FK_GRAPHIC_FKDRAWHISTMATPROGRAM_H

#include "FkGraphicMatProgram.h"

FK_SUPER_CLASS(FkDrawHistMatProgram, FkGraphicMatProgram) {
FK_DEF_CLASS_TYPE_FUNC(FkDrawHistMatProgram)

public:
    FkDrawHistMatProgram(const FkProgramDescription &desc);

    FkDrawHistMatProgram(const FkDrawHistMatProgram &o) = delete;

    virtual ~FkDrawHistMatProgram();

    virtual FkProgramDescription::kType type() override;

    virtual FkResult create() override;

    virtual FkResult addValue(std::shared_ptr<FkComponent> value) override;

    virtual std::string getVertex() override;

    virtual std::string getFragment() override;
};

#endif //FK_GRAPHIC_FKDRAWHISTMATPROGRAM_H
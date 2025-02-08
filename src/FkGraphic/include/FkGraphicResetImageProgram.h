/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: aliminabc@gmail.com

* CREATE TIME: 2024-08-01 23:13:33
*/

#ifndef FK_GRAPHIC_FKGRAPHICRESETIMAGEPROGRAM_H
#define FK_GRAPHIC_FKGRAPHICRESETIMAGEPROGRAM_H

#include "FkGraphicComputeProgram.h"

FK_SUPER_CLASS(FkGraphicResetImageProgram, FkGraphicComputeProgram) {
FK_DEF_CLASS_TYPE_FUNC(FkGraphicResetImageProgram)

public:
    FkGraphicResetImageProgram(const FkProgramDescription &desc);

    FkGraphicResetImageProgram(const FkGraphicResetImageProgram &o) = delete;

    virtual ~FkGraphicResetImageProgram();

    virtual FkProgramDescription::kType type() override;

    virtual std::string getVertex() override;

};

#endif //FK_GRAPHIC_FKGRAPHICRESETIMAGEPROGRAM_H
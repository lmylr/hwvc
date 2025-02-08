/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: aliminabc@gmail.com

* CREATE TIME: 2024-07-16 23:26:35
*/

#ifndef FK_GRAPHIC_FKGRAPHICHISTVIEWPROGRAM_H
#define FK_GRAPHIC_FKGRAPHICHISTVIEWPROGRAM_H

#include "FkGraphicProgram.h"

FK_SUPER_CLASS(FkGraphicHistViewProgram, FkGraphicProgram) {
FK_DEF_CLASS_TYPE_FUNC(FkGraphicHistViewProgram)

public:
    FkGraphicHistViewProgram(const FkProgramDescription &desc);

    FkGraphicHistViewProgram(const FkGraphicHistViewProgram &o) = delete;

    virtual ~FkGraphicHistViewProgram();

    virtual FkProgramDescription::kType type() override;

    virtual FkResult create() override;

    virtual std::string getVertex() override;

    virtual std::string getFragment() override;

    virtual void clear() override;

    virtual FkResult addValue(std::shared_ptr<FkComponent> value) override;

private:
    int32_t uMVPMatLoc = -1;
    int32_t uViewportMatLoc = -1;
    int32_t uTransMatrixLoc = -1;
    int32_t aPosLoc = -1;
    int32_t aCoordinateLoc = -1;
};

#endif //FK_GRAPHIC_FKGRAPHICHISTVIEWPROGRAM_H
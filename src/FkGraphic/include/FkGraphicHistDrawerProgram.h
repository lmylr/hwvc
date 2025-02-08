/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns)

* CREATE TIME: 2024-08-13 22:22:27
*/

#ifndef FK_GRAPHIC_FKGRAPHICHISTDRAWERPROGRAM_H
#define FK_GRAPHIC_FKGRAPHICHISTDRAWERPROGRAM_H

#include "FkGraphicProgram.h"

FK_SUPER_CLASS(FkGraphicHistDrawerProgram, FkGraphicProgram) {
FK_DEF_CLASS_TYPE_FUNC(FkGraphicHistDrawerProgram)

public:
    FkGraphicHistDrawerProgram(const FkProgramDescription &desc);

    FkGraphicHistDrawerProgram(const FkGraphicHistDrawerProgram &o) = delete;

    virtual ~FkGraphicHistDrawerProgram();

    virtual FkProgramDescription::kType type() override;

    virtual FkResult create() override;

    virtual std::string getVertex() override;

    virtual std::string getFragment() override;

    virtual void clear() override;

    virtual FkResult addValue(std::shared_ptr<FkComponent> value) override;

private:
    int32_t aPosLoc = -1;
};

#endif //FK_GRAPHIC_FKGRAPHICHISTDRAWERPROGRAM_H
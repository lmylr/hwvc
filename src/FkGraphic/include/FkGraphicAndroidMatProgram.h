/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: aliminabc@gmail.com

* CREATE TIME: 2024-05-25 11:22:25
*/

#ifndef FK_GRAPHIC_FKGRAPHICANDROIDMATPROGRAM_H
#define FK_GRAPHIC_FKGRAPHICANDROIDMATPROGRAM_H

#include "FkGraphicMatProgram.h"

FK_SUPER_CLASS(FkGraphicAndroidMatProgram, FkGraphicMatProgram) {
FK_DEF_CLASS_TYPE_FUNC(FkGraphicAndroidMatProgram)

public:
    FkGraphicAndroidMatProgram(const FkProgramDescription &desc);

    FkGraphicAndroidMatProgram(const FkGraphicAndroidMatProgram &o) = delete;

    virtual ~FkGraphicAndroidMatProgram();

    virtual FkProgramDescription::kType type() override;

    virtual FkResult create() override;

    virtual std::string getVertex() override;

    virtual std::string getFragment() override;

    virtual void clear() override;

    virtual FkResult addValue(std::shared_ptr<FkComponent> value) override;

};

#endif //FK_GRAPHIC_FKGRAPHICANDROIDMATPROGRAM_H
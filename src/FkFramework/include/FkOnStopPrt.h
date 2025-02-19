/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#ifndef FK_FRAMEWORK_FKONSTOPPROT_H
#define FK_FRAMEWORK_FKONSTOPPROT_H

#include "FkProtocol.h"

FK_SUPER_CLASS(FkOnStopPrt, FkProtocol) {
FK_DEF_CLASS_TYPE_FUNC(FkOnStopPrt)

public:
    FkOnStopPrt();

    FkOnStopPrt(const FkOnStopPrt &o);

    virtual ~FkOnStopPrt();

};

#endif //FK_FRAMEWORK_FKONSTOPPROT_H

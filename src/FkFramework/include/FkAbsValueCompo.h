/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns)

* CREATE TIME: 2024-05-22 00:32:00
*/

#ifndef FK_FRAMEWORK_FKABSVALUECOMPO_H
#define FK_FRAMEWORK_FKABSVALUECOMPO_H

#include "FkComponent.h"

FK_SUPER_TEMPLATE_CLASS(FkAbsValueCompo, FkComponent, typename T) {
FK_DEF_CLASS_TYPE_FUNC(FkAbsValueCompo)

public:
    FkAbsValueCompo() : FkComponent() {}

    FkAbsValueCompo(const FkAbsValueCompo &o) : FkComponent(), value(o.value) {}

    virtual ~FkAbsValueCompo() {}

public:
    std::shared_ptr<T> value = nullptr;
};

#endif //FK_FRAMEWORK_FKABSVALUECOMPO_H
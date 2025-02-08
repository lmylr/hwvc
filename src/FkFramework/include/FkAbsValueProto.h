/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: aliminabc@gmail.com

* CREATE TIME: 2024-06-06 00:01:02
*/

#ifndef FK_FRAMEWORK_FKABSVALUEPROTO_H
#define FK_FRAMEWORK_FKABSVALUEPROTO_H

#include "FkProtocol.h"

FK_SUPER_TEMPLATE_CLASS(FkAbsValueProto, FkProtocol, typename T) {
FK_DEF_CLASS_TYPE_FUNC(FkAbsValueProto)

public:
    FkAbsValueProto() : FkProtocol() {}

    FkAbsValueProto(const FkAbsValueProto &o) : FkProtocol(), value(o.value) {}

    virtual ~FkAbsValueProto() {}

public:
    std::shared_ptr<T> value = nullptr;
};

#endif //FK_FRAMEWORK_FKABSVALUEPROTO_H
/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns)

* CREATE TIME: 2024-06-09 14:42:24
*/

#ifndef FK_BASE_FKANY_H
#define FK_BASE_FKANY_H

#include "FkObject.h"
#include <any>

FK_SUPER_CLASS(FkAny, FkObject) {
FK_DEF_CLASS_TYPE_FUNC(FkAny)

public:
    FkAny();

    FkAny(const std::any &any);

    FkAny(const FkAny &o);

    virtual ~FkAny();

    FkAny &operator=(const std::any &any);

    FkAny &operator=(const FkAny &any);

    template<typename T>
    T get() {
        return std::any_cast<T>(_any);
    }

    std::string getString();

    int32_t getInt32();

    int64_t getInt64();

    float getFloat();

    double getDouble();

private:
    std::any _any;
};

#endif //FK_BASE_FKANY_H
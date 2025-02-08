/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: aliminabc@gmail.com

* CREATE TIME: 2024-06-09 14:42:24
*/

#include "FkAny.h"

FK_IMPL_CLASS_TYPE(FkAny, FkObject)

FkAny::FkAny() : FkObject(), _any(nullptr) {

}

FkAny::FkAny(const std::any &any) : FkObject(), _any(any) {

}

FkAny::FkAny(const FkAny &o) : FkObject(o), _any(o._any) {
}

FkAny::~FkAny() {
}

FkAny &FkAny::operator=(const std::any &any) {
    _any = FkAny(any);
    return *this;
}

FkAny &FkAny::operator=(const FkAny &any) {
    _any = FkAny(any);
    return *this;
}

std::string FkAny::getString() {
    if (!_any.has_value()) {
        return "";
    }
    return get<std::string>();
}

int32_t FkAny::getInt32() {
    if (!_any.has_value()) {
        return 0;
    }
    return get<int32_t>();
}

int64_t FkAny::getInt64() {
    if (!_any.has_value()) {
        return 0;
    }
    return get<int64_t>();
}

float FkAny::getFloat() {
    if (!_any.has_value()) {
        return 0.0f;
    }
    return get<float>();
}

double FkAny::getDouble() {
    if (!_any.has_value()) {
        return 0.0;
    }
    return get<double>();
}

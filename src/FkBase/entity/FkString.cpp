/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#include "FkString.h"

FK_IMPL_CLASS_TYPE(FkString, FkObject)

std::string FkString::valueOf(int32_t value) {
    return valueOf<int32_t>(value);
}

std::string FkString::valueOf(int64_t value) {
    return valueOf<int64_t>(value);
}

std::string FkString::valueOf(float value) {
    return valueOf<float>(value);
}

std::string FkString::valueOf(double value) {
    return valueOf<double>(value);
}

std::string FkString::valueOf(char value) {
    return valueOf<char>(value);
}

std::string FkString::format(const char *format, ...) {
    va_list args;
    va_start(args, format);
    char data[1024];
    sprintf(data, format, args);
    va_end(args);
    return data;
}

FkString::FkString() : FkString("") {

}

FkString::FkString(const char *str)
        : FkObject(), _str(str) {

}

FkString::FkString(const std::string &str)
        : FkObject(), _str(str) {

}

FkString::FkString(const FkString &o)
        : FkObject(), _str(o._str) {

}

FkString::~FkString() {

}

std::string &FkString::str() {
    return _str;
}

const char *FkString::c_str() {
    return _str.c_str();
}

FkString &FkString::append(const std::string &str) {
    _str.append(str);
    return *this;
}

FkString &FkString::append(const char *str) {
    _str.append(str);
    return *this;
}

FkString &FkString::append(int32_t val) {
    return append(valueOf(val));
}

FkString &FkString::append(int64_t val) {
    return append(valueOf(val));
}

FkString &FkString::append(float val) {
    return append(valueOf(val));
}

FkString &FkString::append(double val) {
    return append(valueOf(val));
}

FkString &FkString::append(char val) {
    return append(valueOf(val));
}

size_t FkString::length() {
    return _str.length();
}

void FkString::clear() {
    _str.clear();
}

FkString &FkString::replaceAll(const char *oldStr, const char *newStr) {
    for (std::string::size_type pos(0); pos != std::string::npos; pos += strlen(newStr)) {
        pos = _str.find(oldStr, pos);
        if (pos != std::string::npos)
            _str.replace(pos, strlen(oldStr), newStr);
        else
            break;
    }
    return *this;
}

std::string FkString::toString() {
    return str();
}
/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: aliminabc@gmail.com

* CREATE TIME: 2024-06-09 16:36:25
*/

#include "FkValue.h"

FK_IMPL_CLASS_TYPE(FkValue, FkObject)

FkValue::FkValue()
        : FkObject(), int32Val(0), int64Val(0), floatVal(0), doubleVal(0),
          strVal("") {
}

FkValue::FkValue(const int32_t &value)
        : FkObject(), int32Val(value), int64Val(value), floatVal(value), doubleVal(value),
          strVal("") {

}

FkValue::FkValue(const int64_t &value)
        : FkObject(), int32Val(value), int64Val(value), floatVal(value), doubleVal(value),
          strVal("") {

}

FkValue::FkValue(const float &value)
        : FkObject(), int32Val(value), int64Val(value), floatVal(value), doubleVal(value),
          strVal("") {

}

FkValue::FkValue(const double &value)
        : FkObject(), int32Val(value), int64Val(value), floatVal(value), doubleVal(value),
          strVal("") {

}

FkValue::FkValue(const std::string &value)
        : FkObject(), int32Val(0), int64Val(0), floatVal(0), doubleVal(0), strVal(value) {

}

FkValue::FkValue(const int32_t &int32Val, const int64_t &int64Val, const float &floatVal, const double &doubleVal, const std::string &strVal)
        : FkObject(), int32Val(int32Val), int64Val(int64Val), floatVal(floatVal), doubleVal(doubleVal), strVal(strVal){

}

FkValue::FkValue(const FkValue &o)
        : FkObject(o), int32Val(o.int32Val), int64Val(o.int64Val), floatVal(o.floatVal),
          doubleVal(o.doubleVal), strVal(o.strVal) {

}

FkValue::~FkValue() {

}

std::string FkValue::getString() {
    return strVal;
}

int32_t FkValue::getInt32() {
    return int32Val;
}

int64_t FkValue::getInt64() {
    return int64Val;
}

float FkValue::getFloat() {
    return floatVal;
}

double FkValue::getDouble() {
    return doubleVal;
}

FkValue &FkValue::operator=(const FkValue &value) {
    int32Val = value.int32Val;
    int64Val = value.int64Val;
    floatVal = value.floatVal;
    doubleVal = value.doubleVal;
    strVal = value.strVal;
    return *this;
}

FkValue &FkValue::operator=(const int32_t &value) {
    int32Val = value;
    int64Val = value;
    floatVal = value;
    doubleVal = value;
    strVal = "";
    return *this;
}

FkValue &FkValue::operator=(const int64_t &value) {
    int32Val = value;
    int64Val = value;
    floatVal = value;
    doubleVal = value;
    strVal = "";
    return *this;
}

FkValue &FkValue::operator=(const float &value) {
    int32Val = value;
    int64Val = value;
    floatVal = value;
    doubleVal = value;
    strVal = "";
    return *this;
}

FkValue &FkValue::operator=(const double &value) {
    int32Val = value;
    int64Val = value;
    floatVal = value;
    doubleVal = value;
    strVal = "";
    return *this;
}

FkValue &FkValue::operator=(const std::string &value) {
    int32Val = 0;
    int64Val = 0;
    floatVal = 0;
    doubleVal = 0;
    strVal = value;
    return *this;
}

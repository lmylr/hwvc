/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#include "FkTimeUtils.h"

FkTimeUtils::Cost::Cost(const std::string &tag) : tag(tag) {
    startTime = getCurrentTimeUS();
}

FkTimeUtils::Cost::~Cost() {
    FkLogI(FK_DEF_TAG, "%s cost=%" PRId64, tag.c_str(), (getCurrentTimeUS() - startTime));
}

int64_t FkTimeUtils::getCurrentTimeUS() {
    struct timeval tv;
    gettimeofday(&tv, nullptr);
    return static_cast<long long int>(tv.tv_sec * 1000000.0 + tv.tv_usec);
}

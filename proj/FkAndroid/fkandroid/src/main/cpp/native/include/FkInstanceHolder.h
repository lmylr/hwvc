/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#ifndef FKANDROID_FKINSTANCEHOLDER_H
#define FKANDROID_FKINSTANCEHOLDER_H

#include "FkObject.h"
#include <mutex>
#include <vector>
#include <any>

FK_SUPER_CLASS(FkInstanceHolder, FkObject) {
FK_DEF_CLASS_TYPE_FUNC(FkInstanceHolder)

public:
    static FkInstanceHolder &getInstance();

    FkInstanceHolder(const FkInstanceHolder &o) = delete;

    ~FkInstanceHolder();

    long put(std::any instance);

    void release(long index);

    bool contains(const long index);

    template<typename T>
    T find(const long index) {
        std::lock_guard<std::mutex> guard(mtx);
        if (index > vec.size() || index <= 0) {
            return nullptr;
        }
        auto any = vec[index - 1];
        if (!any.has_value()) {
            return nullptr;
        }
        return std::any_cast<T>(any);
    }

private:
    FkInstanceHolder();

private:
    static std::unique_ptr<FkInstanceHolder> instance;
    std::mutex mtx;
    std::vector<std::any> vec;
};


#endif //FKANDROID_FKINSTANCEHOLDER_H

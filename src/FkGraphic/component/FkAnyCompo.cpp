/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: Alimin
* CREATE TIME: 2022-4-9 23:59:09
*/

#include "FkAnyCompo.h"

FK_IMPL_CLASS_TYPE(FkAnyCompo, FkObject)

FkAnyCompo::FkAnyCompo(std::any any) : FkObject(), any(std::move(any)) {

}

FkAnyCompo::FkAnyCompo(const FkAnyCompo &o) : FkObject(o), any(o.any) {

}

FkAnyCompo::~FkAnyCompo() {
    any = nullptr;
}
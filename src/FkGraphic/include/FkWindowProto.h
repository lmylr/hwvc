/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: Alimin
* CREATE TIME: 2022-2-28 22:22:29
*/

#ifndef FK_GRAPHIC_FKWINDOWPROTO_H
#define FK_GRAPHIC_FKWINDOWPROTO_H

#include "FkProtocol.h"
#include "FkGraphicWindow.h"

FK_SUPER_CLASS(FkWindowProto, FkProtocol) {
FK_DEF_CLASS_TYPE_FUNC(FkWindowProto)

public:
    FkWindowProto();

    FkWindowProto(const FkWindowProto &o);

    virtual ~FkWindowProto();

public:
    std::shared_ptr<FkGraphicWindow> win = nullptr;
};

#endif //FK_GRAPHIC_FKWINDOWPROTO_H
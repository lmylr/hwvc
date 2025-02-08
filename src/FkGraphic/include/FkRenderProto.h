/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#ifndef FK_GRAPHIC_FKRENDERPROTO_H
#define FK_GRAPHIC_FKRENDERPROTO_H

#include "FkProtocol.h"
#include "FkEnvEntity.h"
#include "FkMaterialEntity.h"
#include "FkDeviceEntity.h"

FK_SUPER_CLASS(FkRenderProto, FkProtocol) {
FK_DEF_CLASS_TYPE_FUNC(FkRenderProto)

public:
    FkRenderProto(int64_t reqId);

    FkRenderProto(const FkRenderProto &o);

    virtual ~FkRenderProto();

public:
    int64_t reqId = 0;
    std::shared_ptr<FkEnvEntity> env = nullptr;
    std::shared_ptr<FkMaterialEntity> materials = nullptr;
    std::shared_ptr<FkDeviceEntity> device = nullptr;
};

#endif //FK_GRAPHIC_FKRENDERPROTO_H
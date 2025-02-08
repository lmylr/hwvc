/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns)

* CREATE TIME: 2022-07-08 21:39:19
*/

#ifndef FK_GRAPHIC_FKRENDERDEVICEREQUEST_H
#define FK_GRAPHIC_FKRENDERDEVICEREQUEST_H

#include "FkObject.h"
#include "FkMaterialEntity.h"
#include "FkDeviceEntity.h"
#include <vector>

FK_SUPER_CLASS(FkRenderDeviceRequest, FkObject) {
FK_DEF_CLASS_TYPE_FUNC(FkRenderDeviceRequest)

public:
    FkRenderDeviceRequest(int64_t reqId);

    FkRenderDeviceRequest(const FkRenderDeviceRequest &o) = delete;

    virtual ~FkRenderDeviceRequest();

    size_t size();

    FkResult add(std::shared_ptr<FkMaterialEntity> &materials,
                 std::shared_ptr<FkDeviceEntity> &device);

    std::pair<std::shared_ptr<FkMaterialEntity>, std::shared_ptr<FkDeviceEntity>> &get(int32_t index);

    int64_t getReqId();

private:
    std::vector<std::pair<std::shared_ptr<FkMaterialEntity>, std::shared_ptr<FkDeviceEntity>>> vec;
    int64_t reqId = 0;
};

#endif //FK_GRAPHIC_FKRENDERDEVICEREQUEST_H
/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#include "FkRenderRequest.h"

FK_IMPL_CLASS_TYPE(FkRenderRequest, FkGraphicEntity)

FkRenderRequest::FkRenderRequest() : FkGraphicEntity() {

}

FkRenderRequest::FkRenderRequest(const FkRenderRequest &o)
        : FkGraphicEntity(o), strategy(o.strategy) {

    for (const auto & layer : o.layers) {
        layers.emplace_back(layer);
    }
}

FkRenderRequest::~FkRenderRequest() {
    layers.clear();
}

std::shared_ptr<FkGraphicLayer> FkRenderRequest::getCanvas() {
    auto itr = std::find_if(layers.begin(), layers.end(),
                            [](std::shared_ptr<FkGraphicLayer> item) -> bool {
                                return Fk_CANVAS_ID == item->id;
                            });
    if (itr == layers.end()) {
        return nullptr;
    }
    return *itr;
}

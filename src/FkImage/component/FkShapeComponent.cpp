/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#include "FkShapeComponent.h"

FK_IMPL_CLASS_TYPE(FkShapeComponent, FkGraphicComponent)

FkShapeComponent::FkShapeComponent() : FkGraphicComponent() {

}

FkShapeComponent::FkShapeComponent(const FkShapeComponent &o)
        : FkGraphicComponent(o), type(o.type) {

}

FkShapeComponent::~FkShapeComponent() {

}
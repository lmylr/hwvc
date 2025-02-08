/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns)

* CREATE TIME: 2024-03-09 16:40:44
*/

#include "FkCropComponent.h"

FK_IMPL_CLASS_TYPE(FkCropComponent, FkComponent)

FkCropComponent::FkCropComponent(const FkIntRect &rect) : FkComponent(), rect(rect) {

}

FkCropComponent::FkCropComponent(const FkCropComponent &o) : FkComponent(o), rect(o.rect) {

}

FkCropComponent::~FkCropComponent() {

}
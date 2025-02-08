/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns)

* CREATE TIME: 2022-06-04 23:53:17
*/

#include "FkUpdateLayerModelProto.h"

FK_IMPL_CLASS_TYPE(FkUpdateLayerModelProto, FkObject)

FkUpdateLayerModelProto::FkUpdateLayerModelProto(std::shared_ptr<FkModelInterface> modelInterface)
        : FkProtocol(), modelInterface(modelInterface) {

}

FkUpdateLayerModelProto::FkUpdateLayerModelProto(const FkUpdateLayerModelProto &o)
        : FkProtocol(o), modelInterface(o.modelInterface) {

}

FkUpdateLayerModelProto::~FkUpdateLayerModelProto() {

}
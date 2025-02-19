/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#include "FkRemoteClient.h"

FK_IMPL_CLASS_TYPE(FkRemoteClient, FkSessionClient)

FkRemoteClient::FkRemoteClient() : FkSessionClient() {

}

FkRemoteClient::~FkRemoteClient() {

}

FkResult FkRemoteClient::send(std::shared_ptr<FkSession> session,
                              std::shared_ptr<FkProtocol> protocol) {
    return 0;
}
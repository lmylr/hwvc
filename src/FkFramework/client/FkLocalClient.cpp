/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#include "FkLocalClient.h"

FK_IMPL_CLASS_TYPE(FkLocalClient, FkSessionClient)

FkLocalClient::FkLocalClient() : FkSessionClient() {

}

FkLocalClient::~FkLocalClient() {

}

FkResult FkLocalClient::send(std::shared_ptr<FkSession> session,
                             std::shared_ptr<FkProtocol> protocol) {
    return session->send(protocol);
}

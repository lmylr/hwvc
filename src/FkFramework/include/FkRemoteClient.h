/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#ifndef FK_FRAMEWORK_FKREMOTECLIENT_H
#define FK_FRAMEWORK_FKREMOTECLIENT_H

#include "FkSessionClient.h"

FK_SUPER_CLASS(FkRemoteClient, FkSessionClient) {
FK_DEF_CLASS_TYPE_FUNC(FkRemoteClient)

public:
    FkRemoteClient(const FkRemoteClient &o) = delete;

    FkRemoteClient();

    virtual ~FkRemoteClient();

    virtual FkResult send(std::shared_ptr<FkSession> session, std::shared_ptr<FkProtocol> protocol) override ;
};


#endif //FK_FRAMEWORK_FKREMOTECLIENT_H

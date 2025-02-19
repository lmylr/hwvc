/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#ifndef FK_BASE_FKHANDLER_H
#define FK_BASE_FKHANDLER_H

#include "FkObject.h"
#include "FkMessage.h"
#include "FkLooper.h"
#include "FkDefinition.h"

FK_SUPER_CLASS(FkHandler, FkObject) {
FK_DEF_CLASS_TYPE_FUNC(FkHandler)

public:
    typedef std::function<void(std::shared_ptr<FkMessage> msg)> Callback;
public:
    FkHandler(Callback callback);

    FkHandler(FkLooper *looper, Callback callback);

    ~FkHandler();

    FkResult sendMessage(std::shared_ptr<FkMessage> &msg);

    void dispatchMessage(std::shared_ptr<FkMessage> msg);

private:
    FkResult _enqueueMessage(std::shared_ptr<FkMessage> &msg);

private:
    FkLooper *looper = nullptr;
    Callback callback = nullptr;

};


#endif //FK_BASE_FKHANDLER_H

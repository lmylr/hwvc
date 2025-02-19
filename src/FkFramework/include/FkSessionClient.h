/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#ifndef FK_FRAMEWORK_FKSESSIONEXECUTOR_H
#define FK_FRAMEWORK_FKSESSIONEXECUTOR_H

#include "FkObject.h"
#include "FkSession.h"
#include "FkProtocol.h"

class FkSessionClient;

FK_SUPER_CLASS(FkSessionBuilder, FkObject), public std::enable_shared_from_this<FkSessionBuilder> {
FK_DEF_CLASS_TYPE_FUNC(FkSessionBuilder)
public:
    FkSessionBuilder(std::shared_ptr<FkSessionClient> _client) : FkObject(), client(_client) {
    }

    FkSessionBuilder(const FkSessionBuilder &o) = delete;

    virtual ~FkSessionBuilder() {}

    std::shared_ptr<FkSessionBuilder> with(std::list<std::shared_ptr<FkQuark>> &quarks);

    FkResult send(std::shared_ptr<FkProtocol> proto);

private:
    std::shared_ptr<FkSessionClient> client;
    std::list<std::shared_ptr<FkQuark>> chain;
};

FK_SUPER_CLASS(FkSessionClient, FkObject), public std::enable_shared_from_this<FkSessionClient> {
FK_DEF_CLASS_TYPE_FUNC(FkSessionClient)

public:
    FkSessionClient(const FkSessionClient &o) = delete;

    FkSessionClient();

    virtual ~FkSessionClient();

    virtual FkResult send(std::shared_ptr<FkSession> session, std::shared_ptr<FkProtocol> protocol) = 0;

    FkResult send(std::shared_ptr<FkSession> &session, std::shared_ptr<FkProtocol> proto, std::list<std::shared_ptr<FkQuark>> &chain) {
        for (auto it = chain.begin(); it != chain.end(); ++it) {
            auto ret = session->connectTo(*it);
            if (FK_OK != ret) {
                FkLogW(FK_DEF_TAG, "quickSend session connect failed with ret=%d", ret);
                return ret;
            }
        }
        auto ret = session->open();
        if (FK_OK != ret) {
            FkLogW(FK_DEF_TAG, "quickSend session open failed with ret=%d", ret);
            return ret;
        }
        ret = this->send(session, proto);
        if (FK_OK != ret && FK_SKIP != ret) {
            FkLogW(FK_DEF_TAG, "Process protocol failed with ret=%d", ret);
            auto ret1 = session->close();
            if (FK_OK != ret1) {
                FkLogW(FK_DEF_TAG, "Process protocol failed & close session with ret=%d", ret1);
            }
            return ret;
        }
        return session->close();
    }

    template<typename... Args>
    FkResult quickSend(std::shared_ptr<FkProtocol> proto, Args... quarks) {
        std::list<std::shared_ptr<FkQuark>> chain;
        auto ll = std::initializer_list<std::shared_ptr<FkQuark>>{quarks...};
        for (auto &it : ll) {
            chain.emplace_back(it);
        }
        auto session = FkSession::with({proto->getType(), proto->getClassType().getName()});
        return send(session, proto, chain);
    }

    template<class T, typename... Args>
    FkResult quickSend(std::shared_ptr<T> proto, Args... quarks) {
        std::list<std::shared_ptr<FkQuark>> chain;
        auto ll = std::initializer_list<std::shared_ptr<FkQuark>>{quarks...};
        for (auto &it : ll) {
            chain.emplace_back(it);
        }
        auto session = FkSession::with({proto->getType(), proto->getClassType().getName()});
        return send(session, proto, chain);
    }

    template<class T, typename... Args>
    FkResult quickSend(Args... quarks) {
        std::list<std::shared_ptr<FkQuark>> chain;
        auto ll = std::initializer_list<std::shared_ptr<FkQuark>>{quarks...};
        for (auto &it : ll) {
            chain.emplace_back(it);
        }
        auto proto = std::make_shared<T>();
        auto session = FkSession::with({proto->getType(), proto->getClassType().getName()});
        return send(session, proto, chain);
    }

    template<typename... Args>
    std::shared_ptr<FkSessionBuilder> with(Args... quarks) {
        std::list<std::shared_ptr<FkQuark>> chain;
        auto ll = std::initializer_list<std::shared_ptr<FkQuark>>{quarks...};
        for (auto &it : ll) {
            chain.emplace_back(it);
        }
        auto builder = std::make_shared<FkSessionBuilder>(shared_from_this());
        return builder->with(chain);
    }
};


#endif //FK_FRAMEWORK_FKSESSIONEXECUTOR_H

/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#ifndef FK_FRAMEWORK_FKSIMPLEATOM_H
#define FK_FRAMEWORK_FKSIMPLEATOM_H

#include "FkAtom.h"
#include "FkLocalClient.h"
#include <list>
#include <map>

#define FK_PORT_DESC_SIMPLE_ADD(desc, PRT) \
    desc->add(0, std::static_pointer_cast<FkProtocol>(std::make_shared<PRT>()), \
        reinterpret_cast<FkPort::PortFunc>(&FkSimpleAtom::dispatchNext)) \

FK_SUPER_CLASS(FkConnectChain, FkObject), public std::enable_shared_from_this<FkConnectChain> {
FK_DEF_CLASS_TYPE_FUNC(FkConnectChain)

public:
    FkConnectChain();

    FkConnectChain(const FkConnectChain &o) = delete;

    virtual ~FkConnectChain();

    template<class T>
    std::shared_ptr<FkConnectChain> next() {
        _next(std::make_shared<T>());
        return shared_from_this();
    }

    std::shared_ptr<FkSession> connectSession(FkProtocol::Desc protoDesc, bool reverse = false);

    bool findAllProtocols(std::list<FkProtocol::Desc> &protocols);

    bool empty();

    void clear();

private:
    void _next(std::shared_ptr<FkQuark> quark);

private:
    std::list<std::shared_ptr<FkQuark>> chain;
    std::list<std::shared_ptr<FkQuark>> rChain;
};

FK_SUPER_CLASS(FkSimpleAtom, FkAtom) {
FK_DEF_CLASS_TYPE_FUNC(FkSimpleAtom)

public:
    FkSimpleAtom();

    FkSimpleAtom(const FkSimpleAtom &o) = delete;

    virtual ~FkSimpleAtom();

protected:
    virtual FkResult onCreate() override;

    virtual FkResult onDestroy() override;

    virtual FkResult onStart() override;

    virtual FkResult onStop() override;

    virtual FkResult dispatchNext(std::shared_ptr<FkProtocol> p);

    virtual void onConnect(std::shared_ptr<FkConnectChain> chain) = 0;

    virtual void _prepareDeliveryProtocols();

private:
    void _connectBaseSession();

    void _connectSession();

    void _disconnectSession();

private:
    std::shared_ptr<FkSessionClient> client;
    std::shared_ptr<FkConnectChain> chain;
    std::map<FkProtocol::Type, std::shared_ptr<FkSession>> mSessionMap;
};


#endif //FK_FRAMEWORK_FKSIMPLEATOM_H

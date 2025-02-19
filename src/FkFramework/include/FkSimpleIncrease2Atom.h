/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#ifndef FK_FRAMEWORK_FKSIMPLEINCREASE2ATOM_H
#define FK_FRAMEWORK_FKSIMPLEINCREASE2ATOM_H

#include "FkSimpleAtom.h"

FK_SUPER_CLASS(FkSimpleIncrease2Atom, FkSimpleAtom) {
FK_DEF_CLASS_TYPE_FUNC(FkSimpleIncrease2Atom)

public:
    FkSimpleIncrease2Atom();

    FkSimpleIncrease2Atom(const FkSimpleIncrease2Atom &o) = delete;

    virtual ~FkSimpleIncrease2Atom();

protected:
    virtual void describeProtocols(std::shared_ptr<FkPortDesc> desc) override;

    virtual FkResult onCreate() override;

    virtual FkResult onDestroy() override;

    virtual FkResult onStart() override;

    virtual FkResult onStop() override;

    virtual void onConnect(std::shared_ptr<FkConnectChain> chain) override;

private:
    FkResult _onIncrease2(std::shared_ptr<FkProtocol> p);
};


#endif //FK_FRAMEWORK_FKSIMPLEINCREASE2ATOM_H

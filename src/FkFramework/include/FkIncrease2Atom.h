/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#ifndef FK_FRAMEWORK_FKINCREASE2ATOM_H
#define FK_FRAMEWORK_FKINCREASE2ATOM_H

#include "FkAtom.h"
#include "FkSessionClient.h"
#include "FkSession.h"
#include "FkIncreaseQuark.h"
#include "FkDivideQuark.h"

FK_SUPER_CLASS(FkIncrease2Atom, FkAtom) {
FK_DEF_CLASS_TYPE_FUNC(FkIncrease2Atom)

public:
    FkIncrease2Atom();

    virtual ~FkIncrease2Atom();

protected:
    virtual void describeProtocols(std::shared_ptr<FkPortDesc> desc) override;

    virtual FkResult onCreate() override;

    virtual FkResult onDestroy() override;

    virtual FkResult onStart() override;

    virtual FkResult onStop() override;

private:
    FkIncrease2Atom(const FkIncrease2Atom &o) : FkAtom() {};

private:
    FkResult _onIncrease2(std::shared_ptr<FkProtocol> p);

private:
    std::shared_ptr<FkSessionClient> client;
    std::shared_ptr<FkSession> session = nullptr;
    std::shared_ptr<FkIncreaseQuark> mIncreaseQuark = nullptr;
    std::shared_ptr<FkDivideQuark> mDivideQuark = nullptr;
};


#endif //FK_FRAMEWORK_FKINCREASE2ATOM_H

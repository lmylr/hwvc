/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#ifndef FK_GRAPHIC_FKGRAPHICMVPATOM_H
#define FK_GRAPHIC_FKGRAPHICMVPATOM_H

#include "FkSimpleAtom.h"
#include "FkLocalClient.h"

FK_SUPER_CLASS(FkGraphicModelAtom, FkSimpleAtom) {
FK_DEF_CLASS_TYPE_FUNC(FkGraphicModelAtom)

public:
    FkGraphicModelAtom();

    FkGraphicModelAtom(const FkGraphicModelAtom &o) = delete;

    virtual ~FkGraphicModelAtom();

protected:
    virtual void describeProtocols(std::shared_ptr<FkPortDesc> desc) override;

    virtual void onConnect(std::shared_ptr<FkConnectChain> chain) override;

    virtual FkResult onCreate() override;

    virtual FkResult onDestroy() override;

    virtual FkResult onStart() override;

    virtual FkResult onStop() override;

private:
    FkResult _onDrawLayer(std::shared_ptr<FkProtocol> p);

};


#endif //FK_GRAPHIC_FKGRAPHICMVPATOM_H

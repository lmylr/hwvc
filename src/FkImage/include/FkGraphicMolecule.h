/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#ifndef FK_GRAPHIC_FKGRAPHICMOLECULE_H
#define FK_GRAPHIC_FKGRAPHICMOLECULE_H

#include "FkSimpleMolecule.h"
#include "FkAtom.h"
#include "FkLocalClient.h"

FK_SUPER_CLASS(FkGraphicMolecule, FkSimpleMolecule) {
FK_DEF_CLASS_TYPE_FUNC(FkGraphicMolecule)

public:
    FkGraphicMolecule();

    FkGraphicMolecule(const FkGraphicMolecule &o) = delete;

    virtual ~FkGraphicMolecule();

protected:
    virtual void describeProtocols(std::shared_ptr<FkPortDesc> desc) override;

    virtual FkResult onCreate() override;

    virtual FkResult onDestroy() override;

    virtual FkResult onStart() override;

    virtual FkResult onStop() override;

    virtual void onConnect(std::shared_ptr<FkConnectChain> chain) override;

private:
    FkResult _onDrawLayer(std::shared_ptr<FkProtocol> p);

private:
    std::shared_ptr<FkQuarkContext> context = nullptr;
};


#endif //FK_GRAPHIC_FKGRAPHICMOLECULE_H

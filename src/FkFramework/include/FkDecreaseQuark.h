/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#ifndef FK_FRAMEWORK_FKDECREASEQUARK_H
#define FK_FRAMEWORK_FKDECREASEQUARK_H

#include "FkQuark.h"
#include "FkProtocol.h"

FK_SUPER_CLASS(FkDecreaseQuark, FkQuark) {
FK_DEF_CLASS_TYPE_FUNC(FkDecreaseQuark)

public:
    FkDecreaseQuark();

    virtual ~FkDecreaseQuark();

protected:
    virtual void describeProtocols(std::shared_ptr<FkPortDesc> desc) override;

private:
    FkDecreaseQuark(const FkDecreaseQuark &o) : FkQuark() {};

private:
    FkResult _onDecrease(std::shared_ptr<FkProtocol> p);

};


#endif //FK_FRAMEWORK_FKDECREASEQUARK_H

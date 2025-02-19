/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: Alimin
* CREATE TIME: 2022-2-27 14:40:42
*/

#ifndef FK_GRAPHIC_FKVERTEXCOMPO_H
#define FK_GRAPHIC_FKVERTEXCOMPO_H

#include "FkBufCompo.h"
#include "FkVertexObject.h"
#include "FkBuffer.h"
#include "FkSize.h"

FK_SUPER_CLASS(FkVertexCompo, FkBufCompo) {
FK_DEF_CLASS_TYPE_FUNC(FkVertexCompo)

public:
    FkVertexCompo();

    FkVertexCompo(FkSize size);

    FkVertexCompo(const FkVertexCompo &o);

    virtual ~FkVertexCompo();

    FkResult setup(size_t _countVertex, size_t _countPerVertex, size_t _bytes, void *_data);

    void *data() const;

    size_t size();

private:
    FkVertexCompo(std::shared_ptr<FkBuffer> buf);

public:
    FkVertexDesc desc;
};

#endif //FK_GRAPHIC_FKVERTEXCOMPO_H
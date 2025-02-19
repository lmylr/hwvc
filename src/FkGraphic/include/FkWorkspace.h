/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns)

* CREATE TIME: 2022-05-14 11:04:37
*/

#ifndef FK_GRAPHIC_FKWORKSPACE_H
#define FK_GRAPHIC_FKWORKSPACE_H

#include "FkObject.h"

FK_SUPER_CLASS(FkWorkspace, FkObject) {
FK_DEF_CLASS_TYPE_FUNC(FkWorkspace)

public:
    FkWorkspace(std::string _dir);

    FkWorkspace(const FkWorkspace &o);

    virtual ~FkWorkspace();

    void clear();

    FkResult includeAsSource(const std::string &src, const std::string &cacheName);

    std::string newSourceFilePath(const std::string &fileName);

private:
    std::string dir;
};

#endif //FK_GRAPHIC_FKWORKSPACE_H
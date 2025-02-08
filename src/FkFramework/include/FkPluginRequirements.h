/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns)

* CREATE TIME: 2024-06-07 23:53:19
*/

#ifndef FK_FRAMEWORK_FKPLUGINREQUIREMENTS_H
#define FK_FRAMEWORK_FKPLUGINREQUIREMENTS_H

#include "FkObject.h"
#include <any>
#include <unordered_map>
#include <functional>

FK_SUPER_CLASS(FkPluginRequirements, FkObject) {
FK_DEF_CLASS_TYPE_FUNC(FkPluginRequirements)
public:
    enum Type {
        NONE,
        GL_FBO,
        GL_INPUT,
        GL_INPUT_IMAGE,
        GL_OUTPUT,
        GL_PROGRAM,
        GL_VBO,
        GL_MATRIX,
        GL_TRANS_MATRIX,
        THREAD_GL,
        THREAD_NORMAL,
        RENDER_REQ_ID,
        END,
    };
    typedef std::function<void(Type, const std::any &)> ForEachFunc;

public:
    FkPluginRequirements();

    FkPluginRequirements(const FkPluginRequirements &o);

    virtual ~FkPluginRequirements();

    void add(Type type);

    void add(Type type, const std::any &any);

    bool contains(Type type);

    void forEach(ForEachFunc func);

private:
    std::unordered_map<Type, std::any> _map;
};

#endif //FK_FRAMEWORK_FKPLUGINREQUIREMENTS_H
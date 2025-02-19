/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns)

* CREATE TIME: 2022-05-10 12:58:54
*/

#ifndef FK_GRAPHIC_FKMESHPATH_H
#define FK_GRAPHIC_FKMESHPATH_H

#include "FkCatmullRomPath.h"

FK_SUPER_CLASS(FkMeshPath, FkCatmullRomPath) {
FK_DEF_CLASS_TYPE_FUNC(FkMeshPath)

public:
    FkMeshPath(std::vector<FkDoubleVec2> &meshPoints);

    FkMeshPath(float _strokeWidth, float _pixelsOfSensitivity);

    FkMeshPath(float _strokeWidth, double _avgDistance, float _pixelsOfSensitivity);

    FkMeshPath(const FkMeshPath &o);

    virtual ~FkMeshPath();

    virtual void addPoint(FkDoubleVec2 &point) override;

    virtual size_t readPoints(std::vector<FkDoubleVec2> &_points) override;

    virtual size_t getPoints(std::vector<FkDoubleVec2> &_points) override;

    virtual size_t size() override;

private:
    float strokeWidth = 0.0f;
    std::vector<FkDoubleVec2> meshPoints;
    int readPos = 0;
};

#endif //FK_GRAPHIC_FKMESHPATH_H
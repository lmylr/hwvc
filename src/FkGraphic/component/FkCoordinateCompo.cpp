/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: Alimin
* CREATE TIME: 2022-2-27 14:40:57
*/

#include "FkCoordinateCompo.h"

//每个点占多少字节
#define SIZE_OF_VERTEX  sizeof(float)
//多少个坐标
#define COUNT_VERTEX  4
//每个坐标的维度
#define COUNT_PER_VERTEX  2

FK_IMPL_CLASS_TYPE(FkCoordinateCompo, FkComponent)

FkCoordinateCompo::FkCoordinateCompo() : FkVertexCompo() {

}

FkCoordinateCompo::FkCoordinateCompo(FkFloatRect rectF) : FkVertexCompo() {
    float coordinate[]{
            rectF.left(), rectF.bottom(),//LEFT,BOTTOM
            rectF.right(), rectF.bottom(),//RIGHT,BOTTOM
            rectF.left(), rectF.top(),//LEFT,TOP
            rectF.right(), rectF.top()//RIGHT,TOP
    };
    setup(COUNT_VERTEX, COUNT_PER_VERTEX, SIZE_OF_VERTEX, coordinate);
}

FkCoordinateCompo::FkCoordinateCompo(const FkCoordinateCompo &o) : FkVertexCompo(o) {

}

FkCoordinateCompo::~FkCoordinateCompo() {

}
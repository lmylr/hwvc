/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns)
* CREATE TIME: 2022-2-27 14:40:42
*/

#include "FkVertexCompo.h"

//每个点占多少字节
#define SIZE_OF_VERTEX  sizeof(float)
//多少个坐标
#define COUNT_VERTEX  4
//每个坐标的维度
#define COUNT_PER_VERTEX  2

FK_IMPL_CLASS_TYPE(FkVertexCompo, FkComponent)

FkVertexCompo::FkVertexCompo() : FkVertexCompo(nullptr) {
}

FkVertexCompo::FkVertexCompo(FkSize size) : FkVertexCompo(nullptr) {
    float pos[]{
            -size.getWidth() / 2.0f, -size.getHeight() / 2.0f,//LEFT,BOTTOM
            size.getWidth() / 2.0f, -size.getHeight() / 2.0f,//RIGHT,BOTTOM
            -size.getWidth() / 2.0f, size.getHeight() / 2.0f,//LEFT,TOP
            size.getWidth() / 2.0f, size.getHeight() / 2.0f//RIGHT,TOP
    };
    setup(COUNT_VERTEX, COUNT_PER_VERTEX, SIZE_OF_VERTEX, pos);
}

FkVertexCompo::FkVertexCompo(std::shared_ptr<FkBuffer> buf) : FkBufCompo(buf), desc() {

}

FkVertexCompo::FkVertexCompo(const FkVertexCompo &o) : FkBufCompo(o), desc(o.desc) {

    if (nullptr != o.data()) {
        auto size = o.desc.countVertex * o.desc.countPerVertex * o.desc.format;
        memcpy(data(), o.data(), size);
    }
}

FkVertexCompo::~FkVertexCompo() {
    buf = nullptr;
}

FkResult FkVertexCompo::setup(size_t _countVertex, size_t _countPerVertex,
                              size_t _bytes, void *_data) {
    desc.countVertex = _countVertex;
    desc.countPerVertex = _countPerVertex;
    desc.format = _bytes;
    FkAssert(size() > 0, FK_FAIL);

    buf = FkBuffer::alloc(size());
    memcpy(data(), _data, size());
    return FK_OK;
}

void *FkVertexCompo::data() const {
    return buf ? buf->data() : nullptr;
}

size_t FkVertexCompo::size() {
    return desc.countVertex * desc.countPerVertex * desc.format;
}
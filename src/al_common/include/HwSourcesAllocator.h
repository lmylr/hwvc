//
// Created by limin on 2019/6/15.
//

#ifndef HARDWAREVIDEOCODEC_HWSOURCESALLOCATOR_H
#define HARDWAREVIDEOCODEC_HWSOURCESALLOCATOR_H

#include "Object.h"

class HwSourcesAllocator;

class HwSources : virtual public Object {
public:
    HwSources(HwSourcesAllocator *allocator);

    virtual ~HwSources();

    /**
     * Recycle source by HwSourcesAllocator.
     */
    virtual void recycle();

    /**
     * When allocator is null, this object will be in the detach state.
     * This means this sources isn`t manage by HwSourcesAllocator.
     * Usually，source generated by cloning are not managed
     */
    bool isDetach();

protected:
    HwSourcesAllocator *allocator = nullptr;
};

class HwSourcesAllocator : public Object {
public:
    HwSourcesAllocator();

    virtual ~HwSourcesAllocator();

    virtual bool recycle(HwSources **entity) = 0;

};


#endif //HARDWAREVIDEOCODEC_HWSOURCESALLOCATOR_H

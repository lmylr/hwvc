package com.alimin.fk.source

import androidx.annotation.Keep

@Keep
class FkImageSourceNativeFactory {
    companion object {
        external fun nativeCreateSurface(instance: Any): Long
        external fun nativeDestroy(handle: Long)
    }
}
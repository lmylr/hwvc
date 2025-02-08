package com.alimin.fk.core

import android.util.Log
import java.nio.ByteBuffer


abstract class FkAbsImageSource {
    protected abstract val handle: Long
    companion object {

        external fun nativeCreateSurface(instance: FkAbsImageSource): Long

        external fun nativeCreateCompressed(instance: FkAbsImageSource, buf: ByteBuffer, orientation: Int): Long

        external fun nativeCreateYUV420(instance: FkAbsImageSource, planes: Array<ByteBuffer>, width: Int, height: Int, orientation: Int): Long

        external fun nativeDestroy(handle: Long)
    }

    fun getNativeHandle(): Long = handle

    protected fun finalize() {
        Log.i("FkAbsImageSource", "${javaClass.name} finalize called")
        nativeDestroy(handle)
    }

    abstract fun onCreate(arg0: Int, arg1: Long, arg2: String?): Int
    abstract fun onDestroy(): Int
    abstract fun onRender(arg0: Int, arg1: Long, arg2: String?): Int

    abstract fun getSize(): IntArray

    abstract fun getTimestampInNS(): Long

    abstract fun addOnRenderListener(l: OnRenderListener)

    abstract fun removeOnRenderListener(l: OnRenderListener)

    interface OnRenderListener {
        fun onCreate()
        fun onDestroy()
        fun onRender()
    }
}
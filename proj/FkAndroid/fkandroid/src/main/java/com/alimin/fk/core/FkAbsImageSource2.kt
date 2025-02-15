package com.alimin.fk.core

abstract class FkAbsImageSource2 : FkNativeObject() {
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
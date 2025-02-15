package com.alimin.fk.source

import android.util.Size
import com.alimin.fk.core.FkAbsImageSource2
import com.alimin.fk.utils.FkLogcat
import java.nio.ByteBuffer

class FkYUV420SPImageSource2(private val y: ByteBuffer,
                             private val uv: ByteBuffer,
                             private val size: Size,
                             private val orientation: Int) : FkAbsImageSource2() {

    companion object {
        private val TAG = "FkYUV420SPImageSource2"
    }

    override fun onCreate(arg0: Int, arg1: Long, arg2: String?): Int {
        FkLogcat.i(TAG, "onCreate, tex=$arg0")
        return 0
    }

    override fun onDestroy(): Int {
        FkLogcat.i(TAG, "onDestroy")
        return 0
    }

    override fun onRender(arg0: Int, arg1: Long, arg2: String?): Int {
        return 0
    }

    override fun getSize(): IntArray {
        return intArrayOf(0, 0)
    }

    override fun getTimestampInNS(): Long {
        return System.currentTimeMillis() * 1000000
    }

    override fun addOnRenderListener(l: OnRenderListener) {
    }

    override fun removeOnRenderListener(l: OnRenderListener) {
    }

    override fun onNativeCreate(): Long {
        return 0L
    }

    override fun onNativeDestroy(handle: Long): Boolean {
        return true
    }
}
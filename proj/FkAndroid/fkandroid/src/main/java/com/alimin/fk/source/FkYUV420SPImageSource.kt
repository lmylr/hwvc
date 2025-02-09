package com.alimin.fk.source

import android.graphics.PointF
import android.util.Log
import android.util.Size
import com.alimin.fk.core.FkAbsImageSource
import com.alimin.fk.utils.FkLogcat
import java.nio.ByteBuffer

class FkYUV420SPImageSource: FkAbsImageSource {
    val size: Size
    override val handle: Long

    constructor(y: ByteBuffer, uv: ByteBuffer, size: Size, orientation: Int) {
        this.size = size
        handle = nativeCreateYUV420(this, arrayOf(y, uv), size.width, size.height, orientation)
    }

    constructor(y: ByteBuffer, u: ByteBuffer, v: ByteBuffer, size: Size, orientation: Int) {
        this.size = size
        handle = nativeCreateYUV420(this, arrayOf(y, u, v), size.width, size.height, orientation)
    }

    companion object {
        private val TAG = "FkYUV420SPImageSource"
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

    override fun addOnRenderListener(l: FkAbsImageSource.OnRenderListener) {
    }

    override fun removeOnRenderListener(l: FkAbsImageSource.OnRenderListener) {
    }
}
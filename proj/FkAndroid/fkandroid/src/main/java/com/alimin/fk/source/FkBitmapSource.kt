package com.alimin.fk.source

import androidx.annotation.Keep
import com.alimin.fk.core.FkAbsImageSource
import com.alimin.fk.utils.FkLogcat
import java.nio.ByteBuffer

@Keep
class FkBitmapSource(buf: ByteBuffer, width: Int, height: Int) : FkAbsImageSource() {
    override val handle: Long = nativeCreateBitmap(this, buf, width, height)

    companion object {
        private val TAG = "FkBitmapSource"
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
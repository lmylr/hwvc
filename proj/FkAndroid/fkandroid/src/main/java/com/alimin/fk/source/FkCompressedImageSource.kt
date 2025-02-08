package com.alimin.fk.source

import android.graphics.BitmapFactory
import android.graphics.PointF
import android.media.ExifInterface
import android.opengl.GLES20
import android.os.Build
import android.util.Log
import android.util.Size
import androidx.annotation.Keep
import com.alimin.fk.core.FkAbsImageSource
import java.io.ByteArrayInputStream
import java.nio.ByteBuffer

@Keep
class FkCompressedImageSource(
    buf: ByteBuffer,
    val orientation: Int
) : FkAbsImageSource() {
    override val handle: Long = nativeCreateCompressed(this, buf, orientation)

    companion object {
        private val TAG = "FkCompressedImageSource"
    }

    override fun onCreate(arg0: Int, arg1: Long, arg2: String?): Int {
        Log.i(TAG, "onCreate, tex=$arg0")
        return 0
    }

    override fun onDestroy(): Int {
        Log.i(TAG, "onDestroy")
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
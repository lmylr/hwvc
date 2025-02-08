package com.alimin.fk.source

import android.graphics.Point
import android.graphics.PointF
import android.graphics.SurfaceTexture
import android.util.Log
import android.view.Surface
import androidx.annotation.Keep
import com.alimin.fk.core.FkAbsImageSource
import java.lang.Exception

@Keep
class FkSurfaceTextureSource() : FkAbsImageSource() {
    override val handle: Long = nativeCreateSurface(this)
    private var surface: Surface? = null
    private var surfaceTexture: SurfaceTexture? = null
    private val size = Point(0, 0)
    private val matrix = FloatArray(16)
    private val infoListeners = ArrayList<FkAbsImageSource.OnRenderListener>()
    private var isDestroy = false
    private var reqDestroy = false
    private val scale = PointF(1f, 1f)
    private var createFunc: ((Int, Long, String?) -> Int)? = null
    private var timestampInNS = 0L

    companion object {
        private val TAG = "FkSurfaceTextureSource"
    }

    @Synchronized
    fun create(): Int {
        reqDestroy = false
        surfaceTexture = SurfaceTexture(0)
        surface = Surface(surfaceTexture)
        surfaceTexture?.setOnFrameAvailableListener {
            if (isRending()) {
                val listeners = copyInfoListeners()
                listeners.forEach { listener ->
                    listener.onRender()
                }
            }
        }
        return 0
    }

    @Synchronized
    fun destroy(): Int {
        Log.i(TAG, "destroy")
        reqDestroy = true
        _destroy()
        return 0
    }

    @Synchronized
    private fun _destroy() {
        if (reqDestroy && isDestroy) {
            Log.i(TAG, "_destroy")
            surfaceTexture?.release()
            surfaceTexture = null
            surface?.release()
            surface = null
        }
    }

    @Synchronized
    fun setSize(w: Int, h: Int) {
        size.x = w
        size.y = h
    }

    @Synchronized
    fun allocBuffer() {
        surfaceTexture?.setDefaultBufferSize(size.x, size.y)
        createFunc = this::onCreate
        Log.i(TAG, "allocBuffer")
    }

    @Synchronized
    fun setScale(scaleX: Float, scaleY: Float) {
        scale.x = scaleX
        scale.y = scaleY
    }

    fun getSurface(): Surface? = surface

    override fun onCreate(arg0: Int, arg1: Long, arg2: String?): Int {
        Log.i(TAG, "onCreate tex=$arg0")
        if (arg0 >= 0) {
            synchronized(this) {
                try {
                    if (createFunc != null) {
                        surfaceTexture?.let {
                            it.detachFromGLContext()
                            it.attachToGLContext(arg0)
                        }
                        isDestroy = false
                        createFunc = null
                    }
                } catch (e: Exception) {
                    e.printStackTrace()
                }
            }
            val listeners = copyInfoListeners()
            listeners.forEach {
                it.onCreate()
            }
            return 0
        }
        return -1
    }

    override fun onDestroy(): Int {
        Log.i(TAG, "onDestroy")
        synchronized(this) {
            isDestroy = true
        }
        _destroy()
        val listeners = copyInfoListeners()
        listeners.forEach {
            it.onDestroy()
        }
        return 0
    }

    override fun onRender(arg0: Int, arg1: Long, arg2: String?): Int {
        synchronized(this) {
            createFunc?.invoke(arg0, arg1, arg2)
            if (isRending()) {
                try {
                    surfaceTexture?.updateTexImage()
                } catch (e: Exception) {
                    e.printStackTrace()
                }
            }
        }
        surfaceTexture?.apply {
            timestampInNS = timestamp
            if (timestampInNS > 0) {
                getTransformMatrix(matrix)
                synchronized(this) {
                    matrix[1] *= scale.x
                    matrix[4] *= scale.y
                }
            }
        }
        return 0
    }

    @Synchronized
    private fun isRending() :Boolean = !reqDestroy && !isDestroy

    @Synchronized
    override fun getSize(): IntArray {
        return intArrayOf(size.x, size.y)
    }

    override fun getTimestampInNS(): Long {
        return timestampInNS
    }

    override fun addOnRenderListener(l: FkAbsImageSource.OnRenderListener) {
        synchronized(infoListeners) {
            infoListeners.add(l)
        }
    }

    override fun removeOnRenderListener(l: FkAbsImageSource.OnRenderListener) {
        synchronized(infoListeners) {
            infoListeners.remove(l)
        }
    }

    fun getTransformMatrix(): FloatArray {
        return matrix
    }

    private fun copyInfoListeners(): List<FkAbsImageSource.OnRenderListener> {
        val listeners = ArrayList<FkAbsImageSource.OnRenderListener>()
        synchronized(infoListeners) {
            infoListeners.forEach { listeners.add(it) }
        }
        return listeners
    }
}
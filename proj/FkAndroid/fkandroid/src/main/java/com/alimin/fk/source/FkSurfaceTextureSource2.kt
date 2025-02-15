package com.alimin.fk.source

import android.graphics.Point
import android.graphics.PointF
import android.graphics.SurfaceTexture
import android.view.Surface
import com.alimin.fk.core.FkAbsImageSource
import com.alimin.fk.core.FkAbsImageSource2
import com.alimin.fk.entity.FkResult
import com.alimin.fk.utils.FkLogcat
import java.lang.Exception

class FkSurfaceTextureSource2 : FkAbsImageSource2() {
    private var surface: Surface? = null
    private var surfaceTexture: SurfaceTexture? = null
    private val size = Point(0, 0)
    private val matrix = FloatArray(16)
    private val infoListeners = ArrayList<OnRenderListener>()
    private var isDestroy = false
    private var reqDestroy = false
    private val scale = PointF(1f, 1f)
    private var createFunc: ((Int, Long, String?) -> Int)? = null
    private var timestampInNS = 0L

    companion object {
        private val TAG = "FkSurfaceTextureSource2"
    }

    override fun create(): Int {
        val ret = super.create()
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
        return ret
    }

    override fun destroy(): Int {
        val ret = super.destroy()
        FkLogcat.i(TAG, "destroy")
        reqDestroy = true
        _destroy()
        return ret
    }

    @Synchronized
    private fun _destroy() {
        if (reqDestroy && isDestroy) {
            FkLogcat.i(TAG, "_destroy")
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
        FkLogcat.i(TAG, "allocBuffer")
    }

    @Synchronized
    fun setScale(scaleX: Float, scaleY: Float) {
        scale.x = scaleX
        scale.y = scaleY
    }

    fun getSurface(): Surface? = surface

    override fun onCreate(arg0: Int, arg1: Long, arg2: String?): Int {
        FkLogcat.i(TAG, "onCreate tex=$arg0")
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
        FkLogcat.i(TAG, "onDestroy")
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

    override fun addOnRenderListener(l: OnRenderListener) {
        synchronized(infoListeners) {
            infoListeners.add(l)
        }
    }

    override fun removeOnRenderListener(l: OnRenderListener) {
        synchronized(infoListeners) {
            infoListeners.remove(l)
        }
    }

    fun getTransformMatrix(): FloatArray {
        return matrix
    }

    private fun copyInfoListeners(): List<OnRenderListener> {
        val listeners = ArrayList<OnRenderListener>()
        synchronized(infoListeners) {
            infoListeners.forEach { listeners.add(it) }
        }
        return listeners
    }

    override fun onNativeCreate(): Long {
        return FkImageSourceNativeFactory.nativeCreateSurface(this)
    }

    override fun onNativeDestroy(handle: Long): Boolean {
        FkImageSourceNativeFactory.nativeDestroy(handle)
        return true
    }
}
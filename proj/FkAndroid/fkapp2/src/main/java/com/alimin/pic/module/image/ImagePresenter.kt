package com.alimin.pic.module.image

import android.content.Context
import android.graphics.Color
import android.graphics.Rect
import android.hardware.camera2.CameraManager
import android.util.Size
import android.view.Surface
import com.alimin.fk.core.FkAbsImageSource
import com.alimin.pic.model.ImageEngineModel
import com.alimin.pic.model.impl.ImageEngineModelImpl
import com.alimin.fk.core.FkPaint
import com.alimin.fk.define.kScaleType
import com.alimin.fk.device.FkAbsCamera
import com.alimin.fk.device.FkCamera2
import com.alimin.fk.engine.*
import com.alimin.fk.entity.FkRational
import com.alimin.fk.entity.FkResult
import com.alimin.fk.pb.FkImageLayerOuterClass
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.launch
import java.io.File
import java.nio.ByteBuffer

class ImagePresenter(
    private val view: ImageContract.View,
    workspace: String,
    private val model: ImageEngineModel = ImageEngineModelImpl()
) : ImageContract.Presenter() {
    private val cacheFile: File
    private val engine: FkImage
    private val modelEngine: FkImageModel
    private var curLayer = -1
    private var paint = FkPaint(10, Color.WHITE)
    private var layerUpdateListeners = ArrayList<OnLayerUpdateListener>()
    private var loadStatusListeners = ArrayList<OnDoStatusListener>()
    private var cameraLayer = -1
    private var camera: FkAbsCamera? = null
    private var cameraManager: CameraManager? = null

    init {
        view.presenter = this
        cacheFile = File(File(workspace), "/${System.currentTimeMillis()}.fkp.dir")
        engine = FkImage(cacheFile.absolutePath)
        modelEngine = FkImageModel(engine)
    }

    private fun notifyLayers() {
        getLayers(object : FkGetLayersListener {
            override fun onGetLayers(layers: List<FkImageLayerOuterClass.FkImageLayer>) {
                synchronized(this) {
                    layerUpdateListeners.forEach {
                        GlobalScope.launch(Dispatchers.Main) {
                            it.onLayers(layers)
                        }
                    }
                }
            }
        })
    }

    override fun create() {
        engine.create()
        modelEngine.create()
    }

    override fun start() {
        engine.start()
        modelEngine.start()
        modelEngine.load(cacheFile.absolutePath,
            object : OnDoStatusListener {
                override fun onDone() {
                    synchronized(this) {
                        loadStatusListeners.forEach {
                            GlobalScope.launch(Dispatchers.Main) {
                                it.onDone()
                            }
                        }
                    }

                    GlobalScope.launch(Dispatchers.Main) { notifyLayers() }
                }
            })
        cameraManager?.let {
            createLayerWithCamera()
        }
    }

    override fun stop() {
        if (cameraLayer > 0) {
            val manager = cameraManager
            removeLayer(cameraLayer)
            cameraManager = manager
        }
        modelEngine.save(cacheFile.absolutePath)
        modelEngine.stop()
        engine.stop()
    }

    override fun destroy() {
        camera?.destroy()
        modelEngine.destroy()
        engine.destroy()
        synchronized(this) {
            layerUpdateListeners.clear()
        }
        cacheFile.deleteRecursively()
    }

    override fun notifyRender() {
        engine.notifyRender()
    }

    override fun selectLayer(layerId: Int) {
        if (layerId >= 0) {
            curLayer = layerId
        }
    }

    override fun isSelectedLayer(layerId: Int) : Boolean = curLayer == layerId

    override fun newLayerWithFile(path: String) {
        val layer = engine.newLayerWithFile(path)
        if (curLayer < 0) {
            selectLayer(layer)
        }
        engine.notifyRender()
        if (layer > 0) {
            notifyLayers()
        }
    }

    override fun newLayerWithColor(size: Size, red: Int, green: Int, blue: Int, alpha: Int) {
        val layer = engine.newLayerWithColor(size, red, green, blue, alpha)
        if (curLayer < 0) {
            selectLayer(layer)
        }
        engine.notifyRender()
        if (layer > 0) {
            notifyLayers()
        }
    }

    override fun removeLayer(layerId: Int) {
        val ret = engine.removeLayer(layerId)
        if (FkResult.FK_OK == ret) {
            if (curLayer == layerId) {
                curLayer = -1
            }
            engine.notifyRender()
            if (layerId > 0) {
                notifyLayers()
            }
            if (cameraLayer == layerId) {
                camera?.stop()
                cameraLayer = -1
                cameraManager = null
            }
        }
    }

    override fun detachFromSurface(surface: Surface) {
        engine.detachFromSurface(surface)
    }

    override fun attachToSurface(surface: Surface) {
        engine.attachToSurface(surface, kScaleType.CENTER_INSIDE)
    }

    override fun postTranslate(dx: Int, dy: Int) {
        if (checkCurLayer()) {
            engine.postTranslate(curLayer, dx, dy)
        }
    }

    override fun postRotate(dr: FkRational) {
        if (checkCurLayer()) {
            engine.postRotation(curLayer, dr.num, dr.den)
        }
    }

    override fun postScale(ds: FkRational) {
        if (checkCurLayer()) {
            engine.postScale(curLayer, ds.num.toFloat() / ds.den, ds.num.toFloat() / ds.den)
        }
    }

    override fun getLayers(listener: FkGetLayersListener): Int {
        return modelEngine.getLayers(listener)
    }

    override fun crop(rect: Rect) {
        if (checkCurLayer()) {
//            drawPath(rect.left, rect.top)
//            drawPath(rect.right, rect.bottom)
//            drawPath(rect.left, rect.top)
//            drawPathFinish()
            engine.crop(rect)
        }
    }

    override fun save(file: String) {
        view.onImageSaving()
        engine.save(file, object : FkNativeMsgListener{
            override fun onNativeMsgReceived(
                what: Int,
                arg: Int,
                msg: String?,
                pbObject: ByteBuffer?
            ): Boolean {
                GlobalScope.launch(Dispatchers.Main) {
                    if (arg == 0) {
                        view.onImageSaved(file)
                    } else {
                        view.showError(arg, "Save picture error: $arg")
                    }
                }
                return true
            }
        })
    }

    override fun save() {
        modelEngine.save(cacheFile.absolutePath)
    }

    override fun load(listener: OnDoStatusListener) {
        modelEngine.load(cacheFile.absolutePath, listener)
    }

    private fun checkCurLayer(): Boolean {
        return curLayer >= 0
    }

    @Synchronized
    override fun addLayerUpdateListener(l: OnLayerUpdateListener) {
        layerUpdateListeners.add(l)
    }

    @Synchronized
    override fun removeLayerUpdateListener(l: OnLayerUpdateListener) {
        layerUpdateListeners.remove(l)
    }

    @Synchronized
    override fun addLoadStatusListener(l: OnDoStatusListener) {
        loadStatusListeners.add(l)
    }

    @Synchronized
    override fun removeLoadStatusListener(l: OnDoStatusListener) {
        loadStatusListeners.remove(l)
    }

    override fun drawPath(x: Int, y: Int) {
        engine.drawPath(curLayer, x, y, paint)
    }

    override fun drawPathFinish() {
        engine.drawPathFinish(curLayer)
    }

    override fun getPaint(): FkPaint = paint

    @Synchronized
    override fun createLayerWithCamera(context: Context): Int {
        if (cameraLayer > 0) {
            return -1
        }
        cameraManager = context.getSystemService(Context.CAMERA_SERVICE) as CameraManager
        return createLayerWithCamera()
    }

    private fun createLayerWithCamera(): Int {
        camera = FkCamera2(cameraManager!!)
        camera?.let {
            it.getImageSource().addOnRenderListener(object : FkAbsImageSource.OnRenderListener{
                override fun onCreate() {
                }

                override fun onDestroy() {
                }

                override fun onRender() {
                    engine.notifyRender()
                }
            })
            it.create()
//            it.start()
            cameraLayer = engine.newLayerWithSource(it.getImageSource())
        }
        if (cameraLayer > 0) {
            notifyLayers()
        }
        return cameraLayer
    }
}
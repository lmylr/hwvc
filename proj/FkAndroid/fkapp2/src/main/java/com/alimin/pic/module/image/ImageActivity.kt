package com.alimin.pic.module.image

import android.Manifest
import android.content.Intent
import android.graphics.Point
import android.graphics.PointF
import android.graphics.PorterDuff
import android.media.MediaScannerConnection
import android.os.Bundle
import android.view.*
import android.widget.FrameLayout
import androidx.core.content.ContextCompat
import androidx.core.view.forEachIndexed
import androidx.fragment.app.Fragment
import androidx.fragment.app.FragmentManager
import androidx.viewbinding.ViewBinding
import com.alimin.fk.entity.FkRational
import com.alimin.fk.widgets.FkActSurfaceView
import com.alimin.pic.R
import com.alimin.pic.databinding.ActivityImageBinding
import com.google.android.material.bottomnavigation.BottomNavigationView
import com.lmy.common.adapter.BaseViewPagerAdapter
import com.lmy.common.ext.disableStatusBarPadding
import com.lmy.common.ext.setLightMode
import com.lmy.common.ui.BaseActivity
import com.lmy.common.ui.fragment.BaseLazyFragment
import com.microsoft.fluentui.progress.ProgressBar
import com.microsoft.fluentui.snackbar.Snackbar
import com.microsoft.fluentui.util.createImageView
import pub.devrel.easypermissions.AfterPermissionGranted
import pub.devrel.easypermissions.EasyPermissions
import java.io.File

class OpPagerAdapter(private val presenter: ImageContract.Presenter, val menu:Menu, fm: FragmentManager) : BaseViewPagerAdapter(fm) {
    override fun getCount(): Int = menu.size()

    override fun getItem(position: Int): Fragment {
        return getFragment(position)
            ?: return when (menu.getItem(position).itemId) {
                R.id.action_layer -> OpLayerFragment(presenter)
                R.id.action_crop -> OpCropFragment(presenter)
                R.id.action_paint -> OpPaintFragment(presenter)
                R.id.action_filter -> OpCropFragment(presenter)
                R.id.action_save -> OpExportFragment(presenter)
                else -> OpCropFragment(presenter)
            }
    }

}

class ImageActivity : BaseActivity(),
    ImageContract.View,
    BaseLazyFragment.OnFragmentInteractionListener,
    BottomNavigationView.OnNavigationItemSelectedListener,
    SurfaceHolder.Callback,
    FkActSurfaceView.OnScrollListener,
    FkActSurfaceView.OnRotateListener,
    FkActSurfaceView.OnScaleListener,
    FkActSurfaceView.OnActionListener,
    FkActSurfaceView.OnTouchPosListener {
    override val layoutResID: Int = R.layout.activity_image
    private lateinit var mViewBinding: ActivityImageBinding
    override fun getViewBinding(): ViewBinding = ActivityImageBinding.inflate(layoutInflater).apply {
        mViewBinding = this
    }
    override val isActive: Boolean
        get() = true
    override lateinit var presenter: ImageContract.Presenter
    private val surfaceSize = Point(0, 0)
    private var surfaceView: FkActSurfaceView? = null
    private var pickImagePath: String? = null
    private var mPagerAdapter: OpPagerAdapter? = null

    @AfterPermissionGranted(REQ_PERMISSION)
    override fun initView() {
        setLightMode(false)
        disableStatusBarPadding()
        pickImagePath = intent.getStringExtra("path")
        val workspace = File(externalCacheDir, "workspace")
        if (!workspace.exists()) {
            workspace.mkdirs()
        }
        ImagePresenter(this, workspace.absolutePath)
        val perms = arrayOf(
            Manifest.permission.WRITE_EXTERNAL_STORAGE
        )
        if (EasyPermissions.hasPermissions(this, *perms)) {
            presenter.create()
            surfaceView = FkActSurfaceView(this)
            surfaceView?.holder?.addCallback(this)
            surfaceView?.setOnScrollListener(this)
            surfaceView?.setOnScaleListener(this)
            surfaceView?.setOnRotateListener(this)
            surfaceView?.setOnActionListener(this)
            surfaceView?.setOnTouchPosListener(this)
            val lp = FrameLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT)
            mViewBinding.surfaceHolder.addView(surfaceView, lp)
        } else {
            EasyPermissions.requestPermissions(
                this, "Request write sdcard permission", REQ_PERMISSION, *perms
            )
        }
        mViewBinding.viewPager.isEnabled = false
        mViewBinding.navBar.setOnNavigationItemSelectedListener(this)
        mPagerAdapter = OpPagerAdapter(presenter, mViewBinding.navBar.menu, supportFragmentManager)
        mPagerAdapter?.attach(mViewBinding.viewPager)
    }

    override fun onStart() {
        super.onStart()
        presenter.start()
        if (pickImagePath?.isNotEmpty() == true) {
            presenter.newLayerWithFile(pickImagePath!!)
            pickImagePath = null
        }
    }

    override fun onStop() {
        super.onStop()
        presenter.stop()
    }

    override fun onDestroy() {
        super.onDestroy()
        presenter.destroy()
    }

    override fun surfaceChanged(holder: SurfaceHolder, format: Int, width: Int, height: Int) {
        surfaceSize.x = width
        surfaceSize.y = height
    }

    override fun surfaceDestroyed(holder: SurfaceHolder) {
        presenter.detachFromSurface(holder.surface)
    }

    override fun surfaceCreated(holder: SurfaceHolder) {
        presenter.attachToSurface(holder.surface)
        presenter.notifyRender()
    }

    override fun onRequestPermissionsResult(
        requestCode: Int,
        permissions: Array<out String>,
        grantResults: IntArray
    ) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults)
        EasyPermissions.onRequestPermissionsResult(requestCode, permissions, grantResults, this)
    }

    companion object {
        private const val REQ_PERMISSION = 123
        private const val REQ_PICK_PICTURE = 124
    }

    override fun onScroll(v: SurfaceView, x: Float, y: Float, dx: Float, dy: Float, status: Int) {
        presenter.postTranslate(dx.toInt(), dy.toInt())
    }

    override fun onRotate(v: SurfaceView, dr: FkRational, anchor: PointF) {
        presenter.postRotate(dr)
    }

    override fun onScale(v: SurfaceView, ds: FkRational, anchor: PointF) {
        presenter.postScale(ds)
    }

    override fun onRender(v: SurfaceView) {
        presenter.notifyRender()
    }

    override fun onNavigationItemSelected(item: MenuItem): Boolean {
        mViewBinding.navBar.menu.forEachIndexed { index, it ->
            if (it.itemId == item.itemId) {
                mViewBinding.viewPager.setCurrentItem(index, false)
            }
        }
        return true
    }

    override fun onFragmentInteraction(what: Int, data: Bundle) {
        when (what) {
            R.id.action_hide_bottom_nav ->  mViewBinding.navBar.visibility = View.INVISIBLE
            R.id.action_show_bottom_nav ->  mViewBinding.navBar.visibility = View.VISIBLE
            R.id.action_paint -> {
                surfaceView?.setMode(FkActSurfaceView.Mode.kPaint)
            }
            R.id.action_paint_cancel -> {
                surfaceView?.setMode(FkActSurfaceView.Mode.kMVP)
            }
        }
    }

    override fun showError(error: Int, msg: String) {
        Snackbar.make(window.decorView, msg, Snackbar.LENGTH_SHORT).show()
    }

    override fun onImageSaved(file: String) {
        val checkmarkIconImageView = createImageView(
            com.microsoft.fluentui.ccb.R.drawable.ms_ic_checkmark_24_filled,
            ContextCompat.getColor(this, R.color.colorAccent)
        )
        Snackbar.make(window.decorView, getString(R.string.saved), Snackbar.LENGTH_SHORT)
            .setCustomView(checkmarkIconImageView)
            .show()
        MediaScannerConnection.scanFile(this, arrayOf(file), null) { path, uri ->
            val intent = Intent(Intent.ACTION_MEDIA_SCANNER_SCAN_FILE)
            intent.data = uri
            this.sendBroadcast(intent)
        }
    }

    override fun onImageSaving() {
        val circularProgress = ProgressBar(
            this, null, 0,
            com.microsoft.fluentui.ccb.R.style.Widget_Material3_CircularProgressIndicator_Small
        )
        circularProgress.indeterminateDrawable.setColorFilter(
            ContextCompat.getColor(this, R.color.colorAccent),
            PorterDuff.Mode.SRC_IN
        )
        Snackbar.make(window.decorView, getString(R.string.saving), 600000)
            .setCustomView(circularProgress)
            .show()
    }

    override fun onChange(v: SurfaceView, x: Float, y: Float) {
        presenter.drawPath(x.toInt(), y.toInt())
    }

    override fun onTouchUp(v: SurfaceView, x: Float, y: Float) {
        presenter.drawPathFinish()
    }
}
package com.alimin.pic.module.gallery

import android.Manifest
import android.os.Bundle
import androidx.core.app.ActivityCompat
import androidx.core.graphics.drawable.DrawableCompat
import androidx.viewbinding.ViewBinding
import com.alimin.pic.R
import com.alimin.pic.databinding.ActivityFragmentContainerToolbarBinding
import com.alimin.pic.databinding.FragmentMainBinding
import com.lmy.common.ext.disableStatusBarPadding
import com.lmy.common.ext.setLightMode
import com.lmy.common.ui.BaseActivity
import com.lmy.common.ui.fragment.BaseLazyFragment
import com.lmy.mvp.util.replaceFragmentInActivity
import pub.devrel.easypermissions.AfterPermissionGranted
import pub.devrel.easypermissions.EasyPermissions

class GalleryActivity : BaseActivity(), BaseLazyFragment.OnFragmentInteractionListener {
    override val layoutResID: Int = R.layout.activity_fragment_container_toolbar
    private lateinit var mViewBinding: ActivityFragmentContainerToolbarBinding
    override fun getViewBinding(): ViewBinding = ActivityFragmentContainerToolbarBinding.inflate(layoutInflater).apply {
        mViewBinding = this
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setLightMode(false)
        disableStatusBarPadding()
    }

    @AfterPermissionGranted(REQ_PERMISSION)
    override fun initView() {
        mViewBinding.toolbar.title = getString(R.string.gallery)
        mViewBinding.toolbar.setTitleTextColor(resources.getColor(R.color.white))
        mViewBinding.toolbar.navigationIcon = getDrawable(R.drawable.ic_fluent_crop_layer_24_regular).apply {
            DrawableCompat.setTint(this!!, resources.getColor(R.color.white))
        }
        mViewBinding.toolbar.setNavigationOnClickListener { ActivityCompat.finishAfterTransition(this) }
        val perms = arrayOf(
            Manifest.permission.WRITE_EXTERNAL_STORAGE
        )
        if (EasyPermissions.hasPermissions(this, *perms)) {
            val fragment = supportFragmentManager.findFragmentById(R.id.fragment_container) as GalleryFragment?
                ?: GalleryFragment.newInstance().also {
                    replaceFragmentInActivity(it, R.id.fragment_container)
                }
            GalleryPresenter(fragment)
        } else {
            EasyPermissions.requestPermissions(
                this, "Request write sdcard permission", REQ_PERMISSION, *perms
            )
        }
    }

    override fun onFragmentInteraction(what: Int, data: Bundle) {

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
    }
}
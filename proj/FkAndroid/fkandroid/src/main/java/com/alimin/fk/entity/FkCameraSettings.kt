package com.alimin.fk.entity

import android.util.Size

data class FkCameraSettings(
    var facing: FkCameraFeatures.kFacing,
    var previewSize: Size,
    var pictureSize: Size,
    val reqFeatures: MutableList<FkCameraFeatureKey> = ArrayList()
) {
    init {
        reqFeatures.add(FkCameraFeatureKey.AE_MODE_AUTO)
    }
}
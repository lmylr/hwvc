package com.alimin.fk.entity

import android.util.Size

data class FkCameraSettings(
    var facing: FkCameraFeatures.kFacing,
    var previewSize: Size,
    var pictureSize: Size,
    val reqCameraKeys: MutableList<FkCameraAvailableKey> = ArrayList()
)
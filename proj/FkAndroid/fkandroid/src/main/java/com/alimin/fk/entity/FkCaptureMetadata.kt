package com.alimin.fk.entity

import android.hardware.camera2.CaptureResult
import android.hardware.camera2.TotalCaptureResult
import android.hardware.camera2.params.Face
import android.os.Build
import android.util.Range
import com.alimin.fk.utils.FkCaptureReqUtils

data class FkCaptureMetadata(
    val timestamp: Long,
    val ISO: Int,
    val exposureTime: Long,
    val aperture: Float,
    val exposureCompensation: Int,
    val boostISO: Int,
    var exposureEv: Double,
    val faces: Array<Face>,
    var exposureFactor: Float,
    var focalDistance: Float,
    var aeState: Int,
    var afState: Int
) {

    constructor(exposureTime: Long, iso: Int, metadata: FkCaptureMetadata) : this(
        metadata.timestamp,
        iso,
        exposureTime,
        metadata.aperture,
        metadata.exposureCompensation,
        metadata.boostISO,
        FkCaptureReqUtils.calcExposureBrightness(iso, exposureTime, metadata.aperture),
        metadata.faces,
        metadata.exposureFactor,
        metadata.focalDistance,
        CaptureResult.CONTROL_AE_STATE_INACTIVE,
        CaptureResult.CONTROL_AF_STATE_INACTIVE
    )

    constructor(result: TotalCaptureResult) : this(
        result.get(CaptureResult.SENSOR_TIMESTAMP) ?: 0,
        result.get(CaptureResult.SENSOR_SENSITIVITY) ?: 0,
        result.get(CaptureResult.SENSOR_EXPOSURE_TIME) ?: 0,
        result.get(CaptureResult.LENS_APERTURE) ?: 0.0f,
        result.get(CaptureResult.CONTROL_AE_EXPOSURE_COMPENSATION) ?: 0,
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.N) {
            result.get(CaptureResult.CONTROL_POST_RAW_SENSITIVITY_BOOST) ?: 0
        } else {
            0
        },
        0.0,
        result.get(CaptureResult.STATISTICS_FACES) ?: emptyArray(),
        0.0f,
        result.get(CaptureResult.LENS_FOCAL_LENGTH) ?: 0.0f,
        result.get(CaptureResult.CONTROL_AE_STATE) ?: CaptureResult.CONTROL_AE_STATE_INACTIVE,
        result.get(CaptureResult.CONTROL_AF_STATE) ?: CaptureResult.CONTROL_AF_STATE_INACTIVE
    ) {
        exposureEv = FkCaptureReqUtils.calcExposureBrightness(ISO, exposureTime, aperture)
        exposureFactor = if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            result.get(CaptureResult.REPROCESS_EFFECTIVE_EXPOSURE_FACTOR) ?: 0.0f
        } else {
            0.0f
        }
    }

    fun getSuggestMetadataByISOFirst(
        isoRange: Range<Int>,
        step: Int = 50
    ): FkCaptureMetadata {
        val maxTime = 1000000000 / (if (focalDistance > 0.001f) focalDistance else 10.0f)
        var iso = isoRange.lower
        var time = FkCaptureReqUtils.calcExposureTime(exposureEv, iso, aperture)
        while (time > maxTime && iso <= isoRange.upper) {
            time = FkCaptureReqUtils.calcExposureTime(exposureEv, iso, aperture)
            iso += step
        }
        return FkCaptureMetadata(time, iso, this)
    }

    fun getNextMetadataByISOFirst(
        isoRange: Range<Int>,
        expTimeRange: Range<Long>,
        exposureValue: Int,
        scale:Double = 1.0,
        stepOfISO: Int = 80,
        stepOfExpTime: Long = 16000000L
    ): FkCaptureMetadata {
        val factor = if (exposureValue < 80) 1 else if (exposureValue > 100) -1 else 0
        val maxTime = Math.min((1000000000 / (if (focalDistance > 0.001f) focalDistance else 10.0f)).toLong(), 33333000L)
        var iso = ISO
        var time = exposureTime
        if (factor == 1) {
            if (time < expTimeRange.upper && time < maxTime && stepOfExpTime > 0) {
                time += (stepOfExpTime * scale).toLong()
                time = Math.min(time, maxTime)
            } else if (iso < isoRange.upper) {
                iso += (stepOfISO * scale).toInt()
            }
        } else if (factor == -1) {
            if (iso > isoRange.lower) {
                iso -= (stepOfISO * scale).toInt()
            } else if (time > expTimeRange.lower && stepOfExpTime > 0) {
                time -= (stepOfExpTime * scale).toLong()
            }
        }
        return FkCaptureMetadata(expTimeRange.clamp(time), isoRange.clamp(iso), this)
    }

}
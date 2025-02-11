package com.alimin.fk.core

import com.alimin.fk.entity.FkResult

abstract class FkNativeObject {
    private var handle = 0L
    fun isNull(): Boolean = handle == 0L
    abstract fun onNativeCreate(): Long
    abstract fun onNativeDestroy(handle: Long): Boolean
    fun create(): FkResult {
        val _handle = onNativeCreate()
        synchronized(this) {
            if (_handle != 0L) {
                handle = _handle
                return FkResult.OK
            }
        }
        return FkResult.INVALID_DATA
    }

    fun destroy(): FkResult {
        synchronized(this) {
            val _handle = handle
            handle = 0L
            val state = onNativeDestroy(_handle)
            if (state) {
                return FkResult.OK
            }
        }
        return FkResult.FAIL
    }

    protected fun with(task: (handle: Long) -> FkResult): FkResult {
        synchronized(this) {
            if (isNull()) {
                return FkResult.INVALID_DATA
            }
            return task(handle)
        }
    }
}
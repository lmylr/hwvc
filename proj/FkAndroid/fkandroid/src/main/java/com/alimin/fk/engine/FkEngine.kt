package com.alimin.fk.engine

import androidx.annotation.Keep

@Keep
abstract class FkEngine(private var handle: Long) {

    abstract fun onCreateInstance(): Long
    open fun create() {
        if (isNull()) {
            handle = onCreateInstance()
        }
    }

    open fun destroy() {}
    open fun start() {}
    open fun stop() {}

    protected fun isNull(): Boolean {
        return 0L == handle
    }

    open fun getHandle(): Long {
        return handle
    }

    protected fun releaseHandle() {
        handle = 0L
    }
}
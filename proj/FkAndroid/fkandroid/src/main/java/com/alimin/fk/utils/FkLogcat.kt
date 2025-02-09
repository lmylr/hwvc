package com.alimin.fk.utils

class FkLogcat {
    companion object {
        fun v(tag: String, msg: String) {
            nativeLog(0, tag, msg)
        }

        fun d(tag: String, msg: String) {
            nativeLog(1, tag, msg)
        }

        fun i(tag: String, msg: String) {
            nativeLog(2, tag, msg)
        }

        fun w(tag: String, msg: String) {
            nativeLog(3, tag, msg)
        }

        fun e(tag: String, msg: String) {
            nativeLog(4, tag, msg)
        }

        external fun nativeLog(type: Int, tag: String, msg: String)
    }
}
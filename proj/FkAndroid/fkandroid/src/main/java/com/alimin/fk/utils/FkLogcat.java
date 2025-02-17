package com.alimin.fk.utils;

public class FkLogcat {
    public static void v(String tag, String msg) {
        nativeLog(0, tag, msg);
    }

    public static void d(String tag, String msg) {
        nativeLog(1, tag, msg);
    }

    public static void i(String tag, String msg) {
        nativeLog(2, tag, msg);
    }

    public static void w(String tag, String msg) {
        nativeLog(3, tag, msg);
    }

    public static void e(String tag, String msg) {
        nativeLog(4, tag, msg);
    }

    public native static void nativeLog(int type, String tag, String msg);
}

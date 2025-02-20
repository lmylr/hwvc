package com.alimin.fk.source;

import com.alimin.fk.core.FkNativeObject;
import com.alimin.fk.entity.FkResult;
import com.filmkilns.annotation.FkNativeAuto;

@FkNativeAuto(path = "cpp/native/source")
public class FkNativeTestObject extends FkNativeObject {
    @Override
    public long onNativeCreate() {
        return nativeCreate(false, (byte) 1, '2', (short) 3, 4, 5, 6.0f, 7.0, "888", new Object(), new byte[2]);
    }

    @Override
    public boolean onNativeDestroy(long handle) {
        return nativeDestroy(handle) == FkResult.Companion.getOK().getCode();
    }

    private native long nativeCreate(boolean arg0, byte arg1, char arg2, short arg3, int arg4, long arg5, float arg6, double arg7, String arg8, Object arg9, byte[] arg10);

    private native int nativeDestroy(long handle);
}

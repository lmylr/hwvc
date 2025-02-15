package com.filmkilns.preauto.core;

abstract public class FkNativeObject {
    public interface Task {
        int run(long handle);
    }

    private long handle = 0L;

    public boolean isNull() {
        return handle == 0L;
    }

    public abstract long onNativeCreate();

    public abstract boolean onNativeDestroy(long handle);

    public int create() {
        long _handle = onNativeCreate();
        synchronized (this) {
            if (_handle != 0L) {
                handle = _handle;
                return 0;
            }
        }
        return -1;
    }

    public int destroy() {
        synchronized (this) {
            if (isNull()) {
                return -1;
            }
            long _handle = handle;
            handle = 0L;
            boolean state = onNativeDestroy(_handle);
            if (state) {
                return 0;
            }
        }
        return -1;
    }

    public int with(Task task) {
        synchronized (this) {
            if (isNull()) {
                return -1;
            }
            return task.run(handle);
        }
    }

    @Override
    protected void finalize() throws Throwable {
        super.finalize();
        destroy();
    }
}

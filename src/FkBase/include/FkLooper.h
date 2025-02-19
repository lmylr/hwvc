/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#ifndef FK_BASE_FKLOOPER_H
#define FK_BASE_FKLOOPER_H

#include "FkObject.h"
#include "FkMessage.h"
#include "FkMessageQueue.h"
#include <map>

class FkLooperManager;
class FkHandlerThread;

FK_SUPER_CLASS(FkLooper, FkObject) {
FK_DEF_CLASS_TYPE_FUNC(FkLooper)

public:
    /**
     * 为线程准备一个Looper，如果线程已经存在Looper，则报错
     */
    static void prepare();

    /**
     * 循环消费消息
     */
    static void loop();

    /**
     * 获取当前线程的Looper
     * @return 前线程的Looper
     */
    static FkLooper *myLooper();

    static int64_t myLooperId();

    static void exit();

    FkResult sendMessage(std::shared_ptr<FkMessage> &msg);

    void quit(bool safely);

    void dump();

private:
    friend FkLooperManager;
    friend FkHandlerThread;

    FkLooper();

    FkLooper(const FkLooper &o) = delete;

    ~FkLooper();

    static void prepare(long thread_id);

    static FkLooper *getLooper(long thread_id);

    void _loop();

    void _enqueueMessage(std::shared_ptr<FkMessage> &msg);

    std::shared_ptr<FkMessage> _take();

private:
    std::atomic_bool exiting, exited, exitSafely;
    std::atomic_bool looping;
    FkMessageQueue queue;
    FkMessageQueue queueLevel0;
    std::shared_ptr<FkMessage> curMsg = nullptr;
};

FK_SUPER_CLASS(FkLooperManager, FkObject) {
FK_DEF_CLASS_TYPE_FUNC(FkLooperManager)

private:
    friend FkLooper;

    static FkLooperManager *getInstance();

private:
    FkLooperManager() : FkObject() {}

    FkLooperManager(const FkLooperManager &o) = delete;

    ~FkLooperManager() {}

    /**
     * 为当前线程创建Looper
     * @return 当前线程的Looper
     */
    FkLooper *create(long tid);

    /**
     * 获取当前线程的Looper
     * @return 当前线程的Looper
     */
    FkLooper *get(long tid);

    /**
     * 销毁当前线程的Looper
     */
    void remove(long tid);

private:
    static FkLooperManager *instance;
    std::map<long, FkLooper *> looperMap;
    std::mutex mtx;
};


#endif //FK_BASE_FKLOOPER_H

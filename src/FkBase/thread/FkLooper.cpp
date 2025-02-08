/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#include "FkLooper.h"
#include "FkHandler.h"
#include "FkThread.h"
#include "FkDefinition.h"
#include "FkTimeUtils.h"

#define TAG "FkLooper"

FK_IMPL_CLASS_TYPE(FkLooper, FkObject)
FK_IMPL_CLASS_TYPE(FkLooperManager, FkObject)

void FkLooper::prepare() {
    prepare(FkThread::currentThreadId());
}

void FkLooper::prepare(long thread_id) {
    FkLooper *looper = FkLooperManager::getInstance()->create(thread_id);
    if (nullptr == looper) {
        FkLogE(TAG, "has been called.");
    }
    FkAssert(nullptr != looper, );
}

FkLooper *FkLooper::myLooper() {
    FkLooper *looper = getLooper(FkThread::currentThreadId());
    FkAssert(nullptr != looper, nullptr);
    return looper;
}

FkLooper *FkLooper::getLooper(long thread_id) {
    FkLooper *looper = FkLooperManager::getInstance()->get(thread_id);
    if (nullptr == looper) {
        FkLogE(TAG, "Looper(thread_id=%ld) not found", thread_id);
    }
    return looper;
}

int64_t FkLooper::myLooperId() {
    return reinterpret_cast<int64_t>(myLooper());
}

void FkLooper::loop() {
    myLooper()->_loop();
}

void FkLooper::exit() {
    FkLooperManager::getInstance()->remove(FkThread::currentThreadId());
}

FkLooper::FkLooper() : FkObject() {
    looping = false;
    exiting = false;
    exited = false;
    exitSafely = false;
}

FkLooper::~FkLooper() {
    quit(false);
}

FkResult FkLooper::sendMessage(std::shared_ptr<FkMessage> &msg) {
    if (exiting || exited)
        return FK_FAIL;
    _enqueueMessage(msg);
    return FK_OK;
}

void FkLooper::_enqueueMessage(std::shared_ptr<FkMessage> &msg) {
    if (msg->flags & FkMessage::FLAG_UNIQUE) {
        FkAssertMsg(msg->what != 0, ,"Argument what is invalid for unique message.");
        queue.removeAllMessage(msg->what);
        queueLevel0.removeAllMessage(msg->what);
    }
    if (msg->flags & FkMessage::FLAG_CLEAR) {
        FkAssertMsg(msg->what != 0, ,"Argument what is invalid for clear message.");
        queue.removeAllMessage(msg->what);
        queueLevel0.removeAllMessage(msg->what);
    } else {
        if (msg->flags & FkMessage::FLAG_FIRST_ALWAYS) {
            queueLevel0.offer(msg);
        } else {
            queue.offer(msg);
        }
    }
}

void FkLooper::quit(bool safely) {
    if (exiting || exited)
        return;
    exitSafely = safely;
    exiting = true;
    queue.notify();
}

void FkLooper::_loop() {
    if (looping || exiting || exited) return;
    looping = true;
    for (;;) {
        queue.dump();
        curMsg = _take();
        if (curMsg) {
            if (curMsg->target) {
                curMsg->target->dispatchMessage(curMsg);
            }
        }
        curMsg = nullptr;
        if (exitSafely) {
            if (exiting && 0 == queue.size()) {
                break;
            }
        } else {
            if (exiting) {
                break;
            }
        }
    }
    int64_t time = FkTimeUtils::getCurrentTimeUS();
    while (0 != queue.size()) {
        auto msg = queue.take();
    }
    queue.clear();
    FkLogI(TAG, "clear message cost %lld us.", FkTimeUtils::getCurrentTimeUS() - time);
    exiting = false;
    exited = true;
    looping = false;
}

std::shared_ptr<FkMessage> FkLooper::_take() {
    if (queueLevel0.empty()) {
        return queue.take();
    } else {
        return queueLevel0.take();
    }
}

FkLooperManager *FkLooperManager::instance = new FkLooperManager();

FkLooperManager *FkLooperManager::getInstance() {
    return instance;
}

FkLooper *FkLooperManager::create(long tid) {
    std::lock_guard<std::mutex> guard(mtx);
    auto it = looperMap.find(tid);
    if (looperMap.end() == it) {
        auto *looper = new FkLooper();
        looperMap[tid] = looper;
        return looper;
    }
    return it->second;
}

FkLooper *FkLooperManager::get(long tid) {
    std::lock_guard<std::mutex> guard(mtx);
    auto it = looperMap.find(tid);
    if (looperMap.end() == it) {
        return nullptr;
    }
    return it->second;
}

void FkLooperManager::remove(long tid) {
    std::lock_guard<std::mutex> guard(mtx);
    auto it = looperMap.find(tid);
    if (looperMap.end() != it) {
        looperMap.erase(it);
        auto *looper = it->second;
        delete looper;
    }
}
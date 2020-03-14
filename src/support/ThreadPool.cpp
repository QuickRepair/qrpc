//
// Created by gaojian on 2020/3/14.
//

#include "support/ThreadPool.hpp"

namespace qrpc {
thread_local WorkStealingQueue *ThreadPool::threadWorkQueue;
thread_local unsigned ThreadPool::threadId;
};
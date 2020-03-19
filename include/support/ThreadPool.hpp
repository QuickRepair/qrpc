//
// Created by gaojian on 2020/3/14.
//

#ifndef QRPC_THREADPOOL_HPP
#define QRPC_THREADPOOL_HPP

#include <thread>
#include <atomic>
#include <vector>
#include <future>
#include "ThreadBase.hpp"

namespace qrpc {
class ThreadPool {
	typedef RunnableWrapper TaskType;
public:
	~ThreadPool()
	{
		doneConstruct = true;
		done = true;
		joiner = nullptr;
	}

	static ThreadPool &getInstance() {
		static ThreadPool instance;
		return instance;
	}

	template<typename Runnable, typename ... Args>
	std::future<typename std::result_of<Runnable(Args...)>::type> submit(Runnable runnable, Args ... args)
	{
		typedef typename std::result_of<Runnable(Args...)>::type resultType;
		std::packaged_task<resultType(Args...)> task(runnable);
		std::future<resultType> res(task.get_future());
		RunnableWrapper wrapper(std::move(task), args...);
		if (threadWorkQueue)
			threadWorkQueue->push(std::move(wrapper));
		else
			poolWorkQueue.push(std::move(wrapper));
		return std::move(res);
	}

private:
	ThreadPool()
			: done{false}, joiner{std::make_unique<ThreadJoiner>(threads)}, doneConstruct{false}
	{
		try
		{
			unsigned thread_num = std::thread::hardware_concurrency();
			for (unsigned i = 0; i < thread_num; ++i)
			{
				localWorkQueue.emplace_back(std::make_unique<WorkStealingQueue>());
				threads.emplace_back(std::thread(&ThreadPool::workerThread, this, i));
			}
			doneConstruct = true;
		}
		catch (...)
		{
			done = true;
			doneConstruct = true;
			throw;
		}
	}

	void workerThread(unsigned id)
	{
		while (!doneConstruct)
			std::this_thread::yield();
		threadId = id;
		threadWorkQueue = localWorkQueue[threadId].get();
		while (!done)
			runTask();
	}

	void runTask()
	{
		TaskType task;
		if (popTaskFromLocalQueue(task) || popTaskFromPoolQueue(task) || popTaskFromOtherThread(task))
			task();
		else
			std::this_thread::yield();
	}

	bool popTaskFromLocalQueue(TaskType &task)
	{
		return threadWorkQueue && threadWorkQueue->tryPop(task);
	}

	bool popTaskFromPoolQueue(TaskType &task)
	{
		return poolWorkQueue.tryPop(task);
	}

	bool popTaskFromOtherThread(TaskType &task)
	{
		for (unsigned i = 0; i != localWorkQueue.size(); ++i)
		{
			if (localWorkQueue[i]->trySteal(task))
				return true;
		}
		return false;
	}

	std::atomic_bool done;
	std::atomic_bool doneConstruct;
	std::unique_ptr<ThreadJoiner> joiner;
	ThreadSafeQueue<TaskType> poolWorkQueue;
	std::vector<std::unique_ptr<WorkStealingQueue>> localWorkQueue;
	std::vector<std::thread> threads;
	static thread_local WorkStealingQueue *threadWorkQueue;
	static thread_local unsigned threadId;
};
}


#endif //QRPC_THREADPOOL_HPP

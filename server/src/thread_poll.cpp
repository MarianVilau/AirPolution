#include "thread_poll.h"

namespace Server {

ThreadPoll::ThreadPoll(size_t threads_number): status_(true) {
  Start(threads_number);
}

ThreadPoll::~ThreadPoll() {
  {
    std::unique_lock<std::mutex> lock(task_mutex_);
    status_ = false;
  }
  condition_.notify_all();
  for (std::thread &worker : workers_) {
    worker.join();
  }
}

void ThreadPoll::Start(size_t threads_number) {
  for(size_t index=0; index < threads_number; index++) {
    workers_.emplace_back([this] {
      TaskExecutor();
    });
  }
}

void ThreadPoll::TaskExecutor() {
  while (true) {
    std::function<void()> task;
    {
      std::unique_lock<std::mutex> lock(task_mutex_);
      condition_.wait(lock, [this] { return !status_ || !tasks_.empty(); });
      if (status_ && tasks_.empty()) {
          return;
      }
      task = std::move(tasks_.front());
      tasks_.pop();
    }
    task();
  }
}

}  // namesapce Server
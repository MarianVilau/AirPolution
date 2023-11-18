#ifndef SENSORS_RECEIVER_THREAD_POLL_H_
#define SENSORS_RECEIVER_THREAD_POLL_H_

#include <condition_variable>
#include <mutex>
#include <vector>
#include <thread>
#include <queue>
#include <functional>

namespace Server{

class ThreadPoll {
  public:
    // Creates an instance of ThreadPoll class.
    ThreadPoll(size_t threads_number);
    // Destrois the ThreadPoll instance
    ~ThreadPoll();
    // Starts the thread poll workers.
    void Start(size_t threads_number);
    // Add new task
    template<class F>
    void AddTask(F&& task);  
  private:
    // Execute the tasks
    void TaskExecutor();
    std::thread start_thread_;
    // Defines the workers.
    std::vector<std::thread> workers_;
    // Defines the queue task.
    std::queue<std::function<void()>> tasks_;
    // Defines the task queue mutex.
    std::mutex task_mutex_;
    // Defines the conditional_variable
    std::condition_variable condition_;
    // Defines the state of the server
    bool status_;
};

template<class F>
void ThreadPoll::AddTask(F&& task) {
  {
    std::unique_lock<std::mutex> lock(task_mutex_);
    tasks_.emplace(std::forward<F>(task));
  }
  condition_.notify_one();
}

}  // namespace Server

#endif // SENSORS_RECEIVER_THREAD_POLL_H_
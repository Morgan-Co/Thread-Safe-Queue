#pragma once
#include <condition_variable>
#include <queue>
#include <mutex>

template <typename T>
class safe_queue {
private:
  std::queue<T> queue;
  std::mutex mtx;
  std::condition_variable cv;
  bool stop = false;

public:
  void push(T value) {
    std::lock_guard<std::mutex> lock(mtx);
    queue.push(std::move(value));
    cv.notify_one();
  }

  bool pop(T &value) {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [this] { return !queue.empty() || stop; });

    if (stop && queue.empty()) return false;

    value = std::move(queue.front());
    queue.pop();
    return true;
  }

  void shutdown() {
    {
      std::lock_guard<std::mutex> lock(mtx);
      stop = true;
    }
    cv.notify_all();
  }
};

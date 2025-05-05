#include "thread_pool.h"

void thread_pool::start() {
  int threads = std::thread::hardware_concurrency();
  for (size_t i = 0; i < threads; i++) {
    workers.emplace_back([this] { work(); });
  }
}

void thread_pool::submit(std::function<void()> task) {
  tasks.push(std::move(task));
}

void thread_pool::work() {
  while (true) {
    std::function<void()> task;
    if (!tasks.pop(task)) break;
    task();
  }
}

void thread_pool::shutdown() {
  tasks.shutdown();
  for (std::thread& worker : workers) {
    if (worker.joinable()) worker.join();
  }
}

thread_pool::~thread_pool() {
  shutdown();
}

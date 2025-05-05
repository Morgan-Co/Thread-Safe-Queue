#pragma once
#include <functional>
#include <vector>
#include <thread>
#include "../safe_queue/safe_queue.h"


class thread_pool {
private:
  std::vector<std::thread> workers;
  safe_queue<std::function<void()>> tasks;

public:
  explicit thread_pool() {}
  
  void start();

  void submit(std::function<void()> task);
  
  void work();

  void shutdown();

  ~thread_pool();
};

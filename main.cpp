#include "thread_pool/thread_pool.h"
#include <chrono>
#include <iostream>

void taskA() {
  std::cout << "Executing Task A\n";
}

void taskB() {
  std::cout << "Executing Task B\n";
}


int main() {
    thread_pool pool;
    pool.start();

    for (int i = 0; i < 5; i++) {
      pool.submit(taskA);
      pool.submit(taskB);
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    pool.shutdown();
    return 0;
}

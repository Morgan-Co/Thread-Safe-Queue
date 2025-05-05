cmake_minimum_required(VERSION 3.10)
project(thread_safe_queue)
add_executable(${PROJECT_NAME} main.cpp thread_pool/thread_pool.h thread_pool/thread_pool.cpp safe_queue/safe_queue.h)

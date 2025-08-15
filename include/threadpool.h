//
// Created by paula on 8/10/2025.
//
#pragma once
#ifndef THREADPOOL_H
#define THREADPOOL_H
#include <functional>
#endif //THREADPOOL_H
#include <thread>
#include <vector>
#include <iostream>
#include <queue>
#include <mutex>
#include <functional>
#include <condition_variable>

class ThreadPool {
    public:
    ThreadPool(unsigned int num_threads = std::thread::hardware_concurrency());
    ~ThreadPool();
    void enqueue(std::function<void()> task);

    private:
    std::vector<std::thread> threads;
    std::queue<std::function<void()> > tasks; // Tasks stored must return nothing and not take argument, you must wrap your function and its arguments into a parameterless lambda
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop = false;



};
#include "threadpool.tpp"



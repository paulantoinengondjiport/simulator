//
// Created by paula on 8/10/2025.
//
#pragma once

inline ThreadPool::ThreadPool(unsigned int num_threads) {
    for (unsigned int i = 0; i < num_threads; i++ ) {
        this->threads.emplace_back([this] { // Lambda function using this attributes
            while (true) {
                std::function<void()> task; // This can hold any function that takes no arguments and returns nothing
                {
                    std::unique_lock<std::mutex> lock(this->queue_mutex); // This locks the queue while this thread is accessing it

                    this->condition.wait(lock, [this] { // We wait for the tasks queue to have a task or for the pool to be shut down to continue
                        return !this->tasks.empty() || this->stop;
                    });

                    if (this->stop && this->tasks.empty()) { // If there are no more tasks left and the pool is stopped we exit the thread
                        return;
                    }

                    // Next task is assigned
                    task = std::move(this->tasks.front());
                    this->tasks.pop();
                }

                task(); // We call the task
            }
        });
    }
}

inline ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(this->queue_mutex); // The queue is locked to safely set the stop flag
        this->stop = true;
    }

    this->condition.notify_all(); // Notifies all of the condition.wait()

    for (std::thread &thread : this->threads) { // Wait for all active threads to finish their task
        thread.join();
    }
}


inline void ThreadPool::enqueue(std::function<void()> task)
{
    {
        std::unique_lock<std::mutex> lock(this->queue_mutex); // A lock object is created locking the mutex
        this->tasks.emplace(move(task)); // A new task is placed in the queue
    } // The lock object is automatically destroyed by going out of scope and the mutex is unlocked
    this->condition.notify_one(); // Any thread currently waiting will be notified
}


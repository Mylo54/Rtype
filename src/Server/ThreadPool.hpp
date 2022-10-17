/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** ThreadPool 
*/

#ifndef THREADPOOL_HPP_
#define THREADPOOL_HPP_

#include <functional>
#include <fstream>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <condition_variable>

namespace rtp {
    /// @brief A class holding a thread pool, used for multi-threading
    class ThreadPool {
        public:
            /// @brief ThreadPool object constructor
            /// @param size number of thread
            ThreadPool(int size);
            ~ThreadPool();
            void addTask(std::function<int(void)> fct);
            void executeTask();
            int getActiveThread();
            std::queue<std::function<int(void)>> getFunctions();
        protected:
        private:
            int _finished;
            int _size;
            int _activeThread;
            std::queue<std::thread *> _threads;
            std::queue<std::function<int(void)>> _tasks;
            std::mutex _mutex;
            std::condition_variable _cv;
    };
}

#endif /* !THREADPOOL_HPP_ */
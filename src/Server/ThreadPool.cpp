/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** ThreadPool 
*/

#include "ThreadPool.hpp"

rtp::ThreadPool::ThreadPool(int size)
{
    this->_size = size;
    this->_activeThread = 0;
    this->_finished = 0;
    
    for (int i = 0; i < size; i++) {
        this->_threads.push(new std::thread(&ThreadPool::executeTask, this));
    }
}

rtp::ThreadPool::~ThreadPool()
{
    this->_finished = 1;
    this->_cv.notify_all();
    for (int i = 0; i < this->_size; i++) {
        this->_threads.front()->join();
    }
}

void rtp::ThreadPool::addTask(std::function<int(void)> fct)
{
    std::unique_lock<std::mutex> lk(this->_mutex);
    this->_tasks.push(fct);
    this->_cv.notify_all();
}

void rtp::ThreadPool::executeTask()
{
    std::function<int(void)> fct;

    while (1) {
        std::unique_lock<std::mutex> lk(this->_mutex);
        if (this->_finished == 1)
            return;
        if (this->_tasks.empty()) {
            this->_cv.wait(lk);
        } else {
            this->_activeThread += 1;
            auto task = this->_tasks.front();
            this->_tasks.pop();
            lk.unlock();
            task();
            this->_activeThread -= 1;
        }
    }
}

int rtp::ThreadPool::getActiveThread()
{
    return this->_activeThread;
}

std::queue<std::function<int(void)>> rtp::ThreadPool::getFunctions()
{
    return this->_tasks;
}
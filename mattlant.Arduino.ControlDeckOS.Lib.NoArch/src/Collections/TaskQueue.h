// TaskQueue.h

#ifndef _TASKQUEUE_h
#define _TASKQUEUE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#pragma once
#include <Arduino.h>

template <typename T>
class TaskQueue {
public:
    class TaskQueueIterator {
    public:
        TaskQueueIterator(TaskQueue& queue);
        bool move_next();
        T* get_current();
    private:
        TaskQueue& queue;
        uint8_t current;
        bool firstCall;
    };

    TaskQueue(uint8_t size);
    ~TaskQueue();
    bool enqueue(T* task);
    T* dequeue();
    bool remove(T* task);
    TaskQueueIterator get_iterator();

private:
    T** tasks;
    uint8_t size;
    uint8_t readPointer;
};


template <typename T>
TaskQueue<T>::TaskQueueIterator::TaskQueueIterator(TaskQueue& queue)
    : queue(queue), current(queue.readPointer), firstCall(true) {}

template <typename T>
bool TaskQueue<T>::TaskQueueIterator::move_next() {
    if (firstCall) {
        firstCall = false;
        return queue.tasks[current] != nullptr;
    }
    current = (current + 1) % queue.size;
    if (current == queue.readPointer) return false;
    return queue.tasks[current] != nullptr;
}

template <typename T>
T* TaskQueue<T>::TaskQueueIterator::get_current() {
    return queue.tasks[current];
}

template <typename T>
TaskQueue<T>::TaskQueue(uint8_t size)
    : size(size), readPointer(0) {
    tasks = new T*[size];
    for (uint8_t i = 0; i < size; ++i) {
        tasks[i] = nullptr;
    }
}

template <typename T>
TaskQueue<T>::~TaskQueue() {
    delete[] tasks;
}

template <typename T>
bool TaskQueue<T>::enqueue(T* task) {
    for (uint8_t i = 0; i < size; ++i) {
        if (tasks[i] == nullptr) {
            tasks[i] = task;
            return true;
        }
    }
    return false; // Queue is full
}

template <typename T>
T* TaskQueue<T>::dequeue() {
    if (tasks[readPointer] != nullptr) {
        T* task = tasks[readPointer];
        tasks[readPointer] = nullptr;
        readPointer = (readPointer + 1) % size;
        return task;
    }
    return nullptr; // No task available
}

template <typename T>
bool TaskQueue<T>::remove(T* task) {
    for (uint8_t i = 0; i < size; ++i) {
        if (tasks[i] == task) {
            tasks[i] = nullptr;
            return true;
        }
    }
    return false; // Task not found
}

template <typename T>
typename TaskQueue<T>::TaskQueueIterator TaskQueue<T>::get_iterator() {
    return TaskQueueIterator(*this);
}

#endif


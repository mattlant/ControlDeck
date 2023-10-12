// 
// 
// 

#include "CircularBuffer.h"

template<typename T>
CircularBuffer<T>::CircularBuffer(uint8_t capacity)
    : capacity_(capacity),
      size_(0),
      head_(0),
      tail_(0) {
    buffer_ = new T[capacity];
}

template<typename T>
CircularBuffer<T>::~CircularBuffer() {
    delete[] buffer_;
}

template<typename T>
bool CircularBuffer<T>::push(T item) {
    if (isFull()) {
        return false;
    }
    buffer_[tail_] = item;
    tail_ = (tail_ + 1) % capacity_;
    ++size_;
    return true;
}

template<typename T>
bool CircularBuffer<T>::pop(T& item) {
    if (isEmpty()) {
        return false;
    }
    item = buffer_[head_];
    head_ = (head_ + 1) % capacity_;
    --size_;
    return true;
}

template<typename T>
bool CircularBuffer<T>::isEmpty() const {
    return size_ == 0;
}

template<typename T>
bool CircularBuffer<T>::isFull() const {
    return size_ == capacity_;
}

template<typename T>
uint8_t CircularBuffer<T>::size() const {
    return size_;
}

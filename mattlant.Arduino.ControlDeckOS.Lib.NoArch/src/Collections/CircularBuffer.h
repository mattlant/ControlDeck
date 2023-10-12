// CircularBuffer.h
#pragma once

#ifndef MKERNEL_CIRCULARBUFFER_h
#define MKERNEL_CIRCULARBUFFER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include <new.h>

template<typename T>
class CircularBuffer {
public:
    CircularBuffer(uint8_t capacity);
    ~CircularBuffer();

    bool push(T item);
    bool pop(T& item);
    bool isEmpty() const;
    bool isFull() const;
    uint8_t size() const;

private:
    T* buffer_;
    uint8_t capacity_;
    uint8_t size_;
    uint8_t head_;
    uint8_t tail_;
};


#endif


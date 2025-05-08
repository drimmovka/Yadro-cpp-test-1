#pragma once

#include <stdexcept>

#include "tape_iterator.hpp"

template<typename T>
class Tape {
public:
    using ValueType = T;
    using Iterator = TapeIterator<Tape>;

public:
    explicit Tape(int cap=0)
        : _head_pos(kInitHeadPos)
        , _data(nullptr)
    {
        if (cap < 0) {
            throw std::runtime_error("Capacity cannot be negative");
        }

        _cap = cap;
        
        // calling new with a value of 0 will result in UB, so a check is needed
        if (_cap > 0) {
            _data = new ValueType[_cap];
        }
    }

    Tape& operator=(Tape&& other) {
        if (this != &other) {
            delete[] _data;
            _head_pos = other._head_pos;
            _cap = other._cap;
            _data = std::exchange(other._data, nullptr);
        }
        return *this;
    }

    ~Tape() {
        delete[] _data;
    }

    void moveHeadRight() {
        ++_head_pos;
    }

    void moveHeadLeft() {
        --_head_pos;
    }

    int headPos() const {
        return _head_pos;
    }

    Iterator head() {
        return Iterator(_data + _head_pos);
    }

private:
    static const int kInitHeadPos = -1; // the arithmetic is designed so that the handler doesn't care where init head pos
    int _head_pos;
    int _cap;
    T *_data;

};
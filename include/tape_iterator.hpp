#pragma once

template<typename Tape>
class TapeIterator {
public:
    using ValueType = typename Tape::ValueType;
    using PointerType = ValueType *;
    using ReferenceType = ValueType&;

public:
    TapeIterator(PointerType ptr)
        : _ptr(ptr)
    {}
    
    TapeIterator& operator++() {
        ++_ptr;
        return *this;
    }

    TapeIterator& operator--() {
        --_ptr;
        return *this;
    }

    TapeIterator operator++(int) {
        TapeIterator tmp = (*this);
        ++(*this);
        return tmp;
    }

    TapeIterator operator--(int) {
        TapeIterator tmp = (*this);
        --(*this);
        return tmp;
    }

    PointerType operator->() {
        return _ptr;
    }

    ReferenceType operator*() {
        return *_ptr;
    }

    friend bool operator==(const TapeIterator& lhs, const TapeIterator& rhs) {
        return lhs._ptr == rhs._ptr;
    }

    friend bool operator!=(const TapeIterator& lhs, const TapeIterator& rhs) {
        return !(lhs == rhs);
    }

private:
    PointerType _ptr;
};
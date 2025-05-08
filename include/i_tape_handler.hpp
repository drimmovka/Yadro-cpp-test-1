#pragma once

template<typename T>
class iTapeHandler {
public:
    virtual int tapeSize() const = 0;
    virtual int headPos() const = 0;
    virtual T head() = 0;
    virtual void setHead(T value) = 0;
    virtual void moveTo(int pos) = 0;
    virtual void shift(int offset) = 0;
};
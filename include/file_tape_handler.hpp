#pragma once

#include <fstream>
#include <thread>
#include <chrono>

#include "i_tape_handler.hpp"
#include "delay_settings.hpp"
#include "tape.hpp"


template<typename T>
class FileTapeHandler : public iTapeHandler<T> {
// agreement: operations are not responsible for returning the head to 'init' or 'beforeBegin' position
public:

    explicit FileTapeHandler(const DelaySettings& delay_settings, int mem_limit)
        : _delay_settings(delay_settings)
        , _tape_size(0)
    {
        if (mem_limit < 0) {
            throw std::runtime_error("Memory limit cannot be negative");
        }
        _mem_limit = mem_limit;
        _tape = Tape<T>(mem_limit);
    }


    int tapeSize() const override {
        return _tape_size;
    }

    int memLimit() const {
        return _mem_limit;
    }

    bool readNextMemSeg(std::ifstream& ifs) {
        _tape_size = 0; // resets the size of the current readable tape
        moveTo(-1); // move head to -1

        int value;
        while (_tape_size < _mem_limit) {
            if (!(ifs >> value)) {
                return true; // got to eof of file
            }
            shift(+1);
            setHead(value);
            ++_tape_size;
        }
        return false; // file is not finished yet
    }

    int headPos() const override {
        return _tape.headPos(); 
    }

    T head() override {
        initDelay(_delay_settings.read_delay_ms);
        T value = *_tape.head();
        return value;
    }

    void setHead(T value) override {
        initDelay(_delay_settings.write_delay_ms);
        *_tape.head() = value;
    }

    void moveTo(int pos) override {
        shift(pos - _tape.headPos());
    }

    void shift(int offset) override {
        if (offset < 0) {
            for (int i = 0; i < abs(offset); ++i) {
                initDelay(_delay_settings.move_delay_ms);
                _tape.moveHeadLeft();
            }
        } else {
            for (int i = 0; i < abs(offset); ++i) {
                initDelay(_delay_settings.move_delay_ms);
                _tape.moveHeadRight();
            }
        }
    }

private:
    Tape<T> _tape;
    int _tape_size;
    int _mem_limit;
    DelaySettings _delay_settings;

private:
    void initDelay(int ms) const {
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }
};
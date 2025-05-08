#include "delay_settings.hpp"

DelaySettings::DelaySettings(int read_delay_ms, int write_delay_ms, int move_delay_ms)
{
    if (read_delay_ms < 0) {
        throw std::runtime_error("read_delay_ms cannot be negative");
    }
    if (write_delay_ms < 0) {
        throw std::runtime_error("write_delay_ms cannot be negative");
    }
    if (move_delay_ms < 0) {
        throw std::runtime_error("move_delay_ms cannot be negative");
    }
    this->read_delay_ms = read_delay_ms;
    this->write_delay_ms = write_delay_ms;
    this->move_delay_ms = move_delay_ms;
}
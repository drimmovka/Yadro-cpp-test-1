#pragma once

#include <stdexcept>

struct DelaySettings {
    explicit DelaySettings(int read_delay_ms=0, int write_delay_ms=0, int move_delay_ms=0);
    
    int read_delay_ms;
    int write_delay_ms;
    int move_delay_ms;
};
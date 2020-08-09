#pragma once

#include <stdint.h>

enum bench_opts {
    INTERNAL = 0x01,
    KEYEXPAND = 0x02,
    ADDROUNDKEY = 0x04,
    SUBBYTES = 0x08,
    SHIFTROWS = 0x10,
    MIXCOLUMNS = 0x20,
    CIPHER = 0x40,
    ROUND = 0x80,
};

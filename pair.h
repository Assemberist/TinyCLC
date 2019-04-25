#pragma once
#include <stddef.h>
#include <stdint.h>

#ifndef auto
#define auto __auto_type
#endif

// macros
#define _std_pair(T1, T2) _std_pair_##T1##_##T2
#define std_pair(T1, T2) _std_pair(T1, T2)

#ifndef __make
#define __make(T) _make##T
#endif

#ifndef _make
#define _make(T) __make(T)
#endif

#define PAIRS(T1, T2) typedef struct std_pair(T1, T2){\
    T1 first;\
    T2 second;\
} std_pair(T1, T2);\
std_pair(T1, T2) _make(std_pair(T1, T2))(T1 first, T2 second){\
    std_pair(T1, T2) result;\
    result.first = first;\
    result.second = second;\
    return result;\
}

#define std_make_pair(T1, T2) _make(std_pair(T1, T2))

// methods

#pragma once

#ifndef auto
#define auto __auto_type
#endif

// definitions
#define _std_pair(T1, T2) _std_pair_##T1##_##T2
#define std_pair(T1, T2) _std_pair(T1, T2)

#ifndef __cat
#define __cat(X, Y) X##Y
#endif

#ifndef _cat
#define _cat(X, Y) __cat(X, Y)
#endif

#define PAIRS(T1, T2) typedef struct std_pair(T1, T2){\
    T1 first;\
    T2 second;\
} std_pair(T1, T2);\
std_pair(T1, T2) _cat(_make, std_pair(T1, T2))(T1 first, T2 second){\
    std_pair(T1, T2) result;\
    result.first = first;\
    result.second = second;\
    return result;\
}

// methods
#define std_make_pair(T1, T2) _make(std_pair(T1, T2))
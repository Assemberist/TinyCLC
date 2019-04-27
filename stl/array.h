#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef STD_ARRAY_MAX_SIZE
#define STD_ARRAY_MAX_SIZE 128
#endif

#ifndef auto
#define auto __auto_type
#endif

// definitions
#define _std_array(T) _std_array_##T
#define std_array(T) _std_array(T)

#ifndef __cat
#define __cat(X, Y) X##Y
#endif

#ifndef _cat
#define _cat(X, Y) __cat(X, Y)
#endif


#define ARRAYS(T) typedef struct std_array(T){\
    size_t _size;\
    T data[STD_ARRAY_MAX_SIZE];\
    size_t (*size)(struct std_array(T)*);\
    T* (*at)(struct std_array(T)*, size_t);\
    T* (*begin)(struct std_array(T)*);\
    T* (*end)(struct std_array(T)*);\
    T* (*back)(struct std_array(T)*);\
} std_array(T);\
typedef __typeof__(((std_array(T)*)0)->begin(NULL)) _cat(_iter, std_array(T));\
size_t _cat(_size, std_array(T))(std_array(T)* arr){\
    return arr->_size;\
}\
T* _cat(_at, std_array(T))(std_array(T)* arr, size_t index){\
    if(index >= arr->_size){\
        fprintf(stderr, "std::array [at]: index %d is out of bounds\n", index);\
        exit(EXIT_FAILURE);\
    }\
    return &arr->data[index];\
}\
T* _cat(_begin, std_array(T))(std_array(T)* arr){\
    return arr->data;\
}\
T* _cat(_end, std_array(T))(std_array(T)* arr){\
    return arr->data + arr->_size;\
}\
T* _cat(_back, std_array(T))(std_array(T)* arr){\
    return arr->data + arr->_size - 1;\
}

// methods
#define std_array_iterator(T) _cat(_iter, std_array(T))

#ifndef std_begin
#define std_begin(CONTAINER) (CONTAINER).begin(&(CONTAINER))
#endif

#ifndef std_end
#define std_end(CONTAINER) (CONTAINER).end(&(CONTAINER))
#endif

#ifndef std_back
#define std_back(CONTAINER) (CONTAINER).back(&(CONTAINER))
#endif

#ifndef std_swap
#define std_swap(ITER1, ITER2) *(ITER1) ^= *(ITER2) ^= *(ITER1) ^= *(ITER2)
#endif

#ifndef foreach
#define foreach(CONTAINER) for(__typeof__(std_begin(CONTAINER)) it = std_begin(CONTAINER);\
it < std_end(CONTAINER);\
it++)
#endif


#define construct_std_array(T, SIZE) {\
    ._size = SIZE, \
    .size =  _cat(_size, std_array(T)), \
    .at = _cat(_at, std_array(T)), \
    .begin = _cat(_begin, std_array(T)), \
    .end = _cat(_end, std_array(T)), \
    .back = _cat(_back, std_array(T))\
}

// types (std)
#ifndef STD_ARRAY_DONT_USE_PREDEFINED_TYPES

typedef unsigned char unsigned_char;
typedef unsigned short unsigned_short;
typedef unsigned int unsigned_int;
typedef unsigned long int unsigned_long_int;
typedef unsigned long long int unsigned_long_long_int; 
typedef unsigned long unsigned_long; 
typedef long int long_int;
typedef long long int long_long_int;
typedef long double long_double;

ARRAYS(unsigned_char)
ARRAYS(unsigned_short)
ARRAYS(unsigned_int)
ARRAYS(unsigned_long_int)
ARRAYS(unsigned_long)
ARRAYS(unsigned_long_long_int)
ARRAYS(char)
ARRAYS(short)
ARRAYS(int)
ARRAYS(long_int)
ARRAYS(long_long_int)
ARRAYS(long)

ARRAYS(float)
ARRAYS(double)
ARRAYS(long_double)

// types (stddef)
ARRAYS(size_t)
ARRAYS(ptrdiff_t)
ARRAYS(wchar_t)

// types (stdint)
ARRAYS(int_least8_t)
ARRAYS(int_least16_t)
ARRAYS(int_least32_t)
ARRAYS(int_least64_t)
ARRAYS(uint_least8_t)
ARRAYS(uint_least16_t)
ARRAYS(uint_least32_t)
ARRAYS(uint_least64_t)
ARRAYS(int_fast8_t)
ARRAYS(int_fast16_t)
ARRAYS(int_fast32_t)
ARRAYS(int_fast64_t)
ARRAYS(uint_fast8_t)
ARRAYS(uint_fast16_t)
ARRAYS(uint_fast32_t)
ARRAYS(uint_fast64_t)

ARRAYS(int8_t)
ARRAYS(int16_t)
ARRAYS(int32_t)
ARRAYS(int64_t)
ARRAYS(uint8_t)
ARRAYS(uint16_t)
ARRAYS(uint32_t)
ARRAYS(uint64_t)

ARRAYS(bool)

#endif
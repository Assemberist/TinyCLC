#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef STD_SMALL_VECTOR_MAX_SIZE
#define STD_SMALL_VECTOR_MAX_SIZE 256
#endif

#ifndef auto
#define auto __auto_type
#endif

// definitions
#define _std_small_vector(T) _std_small_vector_##T
#define std_small_vector(T) _std_small_vector(T)

#ifndef __cat
#define __cat(X, Y) X##Y
#endif

#ifndef _cat
#define _cat(X, Y) __cat(X, Y)
#endif


#define SMALL_VECTORS(T) typedef struct std_small_vector(T){\
    size_t _size;\
    T _data[STD_SMALL_VECTOR_MAX_SIZE];\
    void (*clear)(struct std_small_vector(T)*);\
    size_t (*size)(struct std_small_vector(T)*);\
    const T* (*data)(struct std_small_vector(T)*);\
    T* (*at)(struct std_small_vector(T)*, size_t);\
    T* (*begin)(struct std_small_vector(T)*);\
    T* (*end)(struct std_small_vector(T)*);\
    T* (*back)(struct std_small_vector(T)*);\
    void (*push_back)(struct std_small_vector(T)*, T);\
    T (*pop_back)(struct std_small_vector(T)*);\
} std_small_vector(T);\
typedef T* _cat(_iter, std_small_vector(T));\
void _cat(_clear, std_small_vector(T))(std_small_vector(T)* svec){\
    svec->_size = 0;\
}\
size_t _cat(_size, std_small_vector(T))(std_small_vector(T)* svec){\
    return svec->_size;\
}\
const T* _cat(_data, std_small_vector(T))(std_small_vector(T)* svec){\
    return svec->_data;\
}\
T* _cat(_at, std_small_vector(T))(std_small_vector(T)* svec, size_t index){\
    if(index >= svec->_size){\
        fprintf(stderr, "std::small_vector [at]: index %d is out of bounds\n", index);\
        exit(EXIT_FAILURE);\
    }\
    return &svec->_data[index];\
}\
T* _cat(_begin, std_small_vector(T))(std_small_vector(T)* svec){\
    return svec->_data;\
}\
T* _cat(_end, std_small_vector(T))(std_small_vector(T)* svec){\
    return svec->_data + svec->_size;\
}\
T* _cat(_back, std_small_vector(T))(std_small_vector(T)* svec){\
    return svec->_data + svec->_size - 1;\
}\
void _cat(_push_back, std_small_vector(T))(std_small_vector(T)* svec, T value){\
    svec->_size++;\
    if(svec->_size > STD_SMALL_VECTOR_MAX_SIZE){\
        fprintf(stderr, "std::small_vector [push_back]: out of reserve\n");\
        exit(EXIT_FAILURE);\
    }\
    *svec->back(svec) = value;\
}\
T _cat(_pop_back, std_small_vector(T))(std_small_vector(T)* svec){\
    T result = *svec->back(svec);\
    svec->_size--;\
    return result;\
}

// methods
#define std_small_vector_iterator(T) _cat(_iter, std_small_vector(T))

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


#define std_small_vector_default(T) (std_small_vector(T)){\
    ._size = 0, \
    .clear = _cat(_clear, std_small_vector(T)), \
    .size = _cat(_size, std_small_vector(T)), \
    .data = _cat(_data, std_small_vector(T)), \
    .at = _cat(_at, std_small_vector(T)), \
    .begin = _cat(_begin, std_small_vector(T)), \
    .end = _cat(_end, std_small_vector(T)), \
    .back = _cat(_back, std_small_vector(T)), \
    .push_back = _cat(_push_back, std_small_vector(T)), \
    .pop_back = _cat(_pop_back, std_small_vector(T))\
}

// types (std)
#ifndef STD_SMALL_VECTOR_DONT_USE_PREDEFINED_TYPES

typedef unsigned char unsigned_char;
typedef unsigned short unsigned_short;
typedef unsigned int unsigned_int;
typedef unsigned long int unsigned_long_int;
typedef unsigned long long int unsigned_long_long_int; 
typedef unsigned long unsigned_long; 
typedef long int long_int;
typedef long long int long_long_int;
typedef long double long_double;

SMALL_VECTORS(unsigned_char)
SMALL_VECTORS(unsigned_short)
SMALL_VECTORS(unsigned_int)
SMALL_VECTORS(unsigned_long_int)
SMALL_VECTORS(unsigned_long)
SMALL_VECTORS(unsigned_long_long_int)
SMALL_VECTORS(char)
SMALL_VECTORS(short)
SMALL_VECTORS(int)
SMALL_VECTORS(long_int)
SMALL_VECTORS(long_long_int)
SMALL_VECTORS(long)

SMALL_VECTORS(float)
SMALL_VECTORS(double)
SMALL_VECTORS(long_double)

// types (stddef)
SMALL_VECTORS(size_t)
SMALL_VECTORS(ptrdiff_t)
SMALL_VECTORS(wchar_t)

// types (stdint)
SMALL_VECTORS(int_least8_t)
SMALL_VECTORS(int_least16_t)
SMALL_VECTORS(int_least32_t)
SMALL_VECTORS(int_least64_t)
SMALL_VECTORS(uint_least8_t)
SMALL_VECTORS(uint_least16_t)
SMALL_VECTORS(uint_least32_t)
SMALL_VECTORS(uint_least64_t)
SMALL_VECTORS(int_fast8_t)
SMALL_VECTORS(int_fast16_t)
SMALL_VECTORS(int_fast32_t)
SMALL_VECTORS(int_fast64_t)
SMALL_VECTORS(uint_fast8_t)
SMALL_VECTORS(uint_fast16_t)
SMALL_VECTORS(uint_fast32_t)
SMALL_VECTORS(uint_fast64_t)

SMALL_VECTORS(int8_t)
SMALL_VECTORS(int16_t)
SMALL_VECTORS(int32_t)
SMALL_VECTORS(int64_t)
SMALL_VECTORS(uint8_t)
SMALL_VECTORS(uint16_t)
SMALL_VECTORS(uint32_t)
SMALL_VECTORS(uint64_t)

SMALL_VECTORS(bool)

#endif
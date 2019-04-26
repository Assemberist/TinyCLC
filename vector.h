#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define STD_VECTOR_CAPACITY_GROW 1.618

#ifndef auto
#define auto __auto_type
#endif

// definitions
#define _std_vector(T) _std_vector_##T
#define std_vector(T) _std_vector(T)

#ifndef __cat
#define __cat(X, Y) X##Y
#endif

#ifndef _cat
#define _cat(X, Y) __cat(X, Y)
#endif


#define VECTORS(T) typedef struct std_vector(T){\
    size_t _size, _capacity;\
    T* _data;\
    void (*reserve)(struct std_vector(T)*, size_t);\
    void (*destroy)(struct std_vector(T)*);\
    void (*clear)(struct std_vector(T)*);\
    T* (*at)(struct std_vector(T)*, size_t);\
    size_t (*size)(struct std_vector(T)*);\
    size_t (*capacity)(struct std_vector(T)*);\
    const T*(*data)(struct std_vector(T)*);\
    T* (*begin)(struct std_vector(T)*);\
    T* (*end)(struct std_vector(T)*);\
    T* (*back)(struct std_vector(T)*);\
    void (*push_back)(struct std_vector(T)*, T);\
    T (*pop_back)(struct std_vector(T)*);\
} std_vector(T);\
void _cat(_reserve, std_vector(T))(std_vector(T)* vec, size_t size){\
    vec->_capacity = size;\
    vec->_data = malloc(size * sizeof(T));\
}\
void _cat(_destroy, std_vector(T))(std_vector(T)* vec){\
    vec->_capacity = 0;\
    vec->_size = 0;\
    free(vec->_data);\
    vec->_data = NULL;\
}\
void _cat(_clear, std_vector(T))(std_vector(T)* vec){\
    vec->_size = 0;\
}\
T* _cat(_at, std_vector(T))(std_vector(T)* vec, size_t index){\
    if(index >= vec->_size){\
        fprintf(stderr, "std::vector [at]: index %d is out of bounds\n", index);\
        exit(EXIT_FAILURE);\
    }\
    return &vec->_data[index];\
}\
size_t _cat(_size, std_vector(T))(std_vector(T)* vec){\
    return vec->_size;\
}\
size_t _cat(_capacity, std_vector(T))(std_vector(T)* vec){\
    return vec->_capacity;\
}\
const T* _cat(_data, std_vector(T))(std_vector(T)* vec){\
    return vec->_data;\
}\
T* _cat(_begin, std_vector(T))(std_vector(T)* vec){\
    return vec->_data;\
}\
T* _cat(_end, std_vector(T))(std_vector(T)* vec){\
    return vec->_data + vec->_size;\
}\
T* _cat(_back, std_vector(T))(std_vector(T)* vec){\
    return vec->_data + vec->_size - 1;\
}\
void _cat(_push_back, std_vector(T))(std_vector(T)* vec, T value){\
    vec->_size++;\
    if(vec->_size > vec->_capacity){\
        vec->_capacity *= STD_VECTOR_CAPACITY_GROW;\
        vec->_data = realloc(vec->_data, vec->_capacity * sizeof(T));\
    }\
    *vec->back(vec) = value;\
}\
T _cat(_pop_back, std_vector(T))(std_vector(T)* vec){\
    T result = *vec->back(vec);\
    vec->_size--;\
    return result;\
}

// methods
#ifndef std_begin
#define std_begin(CONTAINER) (CONTAINER).begin(&CONTAINER)
#endif

#ifndef std_end
#define std_end(CONTAINER) (CONTAINER).end(&CONTAINER)
#endif

#ifndef std_back
#define std_back(CONTAINER) (CONTAINER).back(&CONTAINER)
#endif

#ifndef std_swap
#define std_swap(ITER1, ITER2) *(ITER1) ^= *(ITER2) ^= *(ITER1) ^= *(ITER2)
#endif

#ifndef foreach
#define foreach(CONTAINER) for(__typeof__(std_begin(CONTAINER)) it = std_begin(CONTAINER);\
it < std_end(CONTAINER);\
it++)
#endif

#define std_vector_default(T) {\
    0, 0, NULL, \
    _cat(_reserve, std_vector(T)), \
    _cat(_destroy, std_vector(T)), \
    _cat(_clear, std_vector(T)), \
    _cat(_at, std_vector(T)), \
    _cat(_size, std_vector(T)), \
    _cat(_capacity, std_vector(T)), \
    _cat(_data, std_vector(T)), \
    _cat(_begin, std_vector(T)), \
    _cat(_end, std_vector(T)), \
    _cat(_back, std_vector(T)), \
    _cat(_push_back, std_vector(T)), \
    _cat(_pop_back, std_vector(T))\
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

VECTORS(unsigned_char)
VECTORS(unsigned_short)
VECTORS(unsigned_int)
VECTORS(unsigned_long_int)
VECTORS(unsigned_long)
VECTORS(unsigned_long_long_int)
VECTORS(char)
VECTORS(short)
VECTORS(int)
VECTORS(long_int)
VECTORS(long_long_int)
VECTORS(long)

VECTORS(float)
VECTORS(double)
VECTORS(long_double)

// types (stddef)
VECTORS(size_t)
VECTORS(ptrdiff_t)
VECTORS(wchar_t)

// types (stdint)
VECTORS(int_least8_t)
VECTORS(int_least16_t)
VECTORS(int_least32_t)
VECTORS(int_least64_t)
VECTORS(uint_least8_t)
VECTORS(uint_least16_t)
VECTORS(uint_least32_t)
VECTORS(uint_least64_t)
VECTORS(int_fast8_t)
VECTORS(int_fast16_t)
VECTORS(int_fast32_t)
VECTORS(int_fast64_t)
VECTORS(uint_fast8_t)
VECTORS(uint_fast16_t)
VECTORS(uint_fast32_t)
VECTORS(uint_fast64_t)

VECTORS(int8_t)
VECTORS(int16_t)
VECTORS(int32_t)
VECTORS(int64_t)
VECTORS(uint8_t)
VECTORS(uint16_t)
VECTORS(uint32_t)
VECTORS(uint64_t)

VECTORS(bool)

#endif
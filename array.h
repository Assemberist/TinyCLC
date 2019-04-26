#pragma once
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef STD_ARRAY_MAX_SIZE
#define STD_ARRAY_MAX_SIZE 256
#endif

#ifndef auto
#define auto __auto_type
#endif

// macros
#define _std_array(T) _std_array_##T
#define std_array(T) _std_array(T)

#define ARRAYS(T) typedef struct std_array(T){\
    size_t size;\
    T data[STD_ARRAY_MAX_SIZE];\
} std_array(T);


#define std_begin(ARRAY) (ARRAY).data
#define std_end(ARRAY) ((ARRAY).data + (ARRAY).size)
#define std_back(ARRAY) (std_end(ARRAY) - 1)

#define std_swap(ITER1, ITER2) *(ITER1) ^= *(ITER2) ^= *(ITER1) ^= *(ITER2)

#define foreach(ARRAY) for(__typeof__((ARRAY).data[0])* it = std_begin(ARRAY);\
it < std_end(ARRAY);\
it++)


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

// methods
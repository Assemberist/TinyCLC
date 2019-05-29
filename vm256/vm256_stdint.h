#pragma once

#ifndef NULL
#define NULL (void*)0
#endif

#ifdef VM_TARGET_ARCH16
typedef unsigned short int vm_size_t;
#else
    #ifdef VM_TARGET_ARCH32
    typedef unsigned int vm_size_t;
    #else
        #ifdef VM_TARGET_ARCH64
        typedef unsigned long long vm_size_t;
        #endif
    #endif
#endif


// unsigned
typedef unsigned char vm_uint8_t;
typedef struct vm_uint16_t{
    vm_uint8_t bytes[2];
} vm_uint16_t;
typedef struct vm_uint32_t{
    vm_uint8_t bytes[4];
} vm_uint32_t;
typedef struct vm_uint64_t{
    vm_uint8_t bytes[8];
} vm_uint64_t;
typedef struct vm_uint128_t{
    vm_uint8_t bytes[16];
} vm_uint128_t;
typedef struct vm_uint256_t{
    vm_uint8_t bytes[32];
} vm_uint256_t;

// signed
typedef char vm_int8_t;
typedef struct vm_int16_t{
    vm_int8_t bytes[2];
} vm_int16_t;
typedef struct vm_int32_t{
    vm_int8_t bytes[4];
} vm_int32_t;
typedef struct vm_int64_t{
    vm_int8_t bytes[8];
} vm_int64_t;
typedef struct vm_int128_t{
    vm_int8_t bytes[16];
} vm_int128_t;
typedef struct vm_int256_t{
    vm_int8_t bytes[32];
} vm_int256_t;

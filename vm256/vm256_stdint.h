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

typedef enum _VM_BOOL {false = 0, true} vm_bool;

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


// operations
#define vm_equal16(a, b) (\
    ((a).bytes[0] == (b).bytes[0]) && \
    ((a).bytes[1] == (b).bytes[1])\
)
#define vm_equal32(a, b) (\
    ((a).bytes[0] == (b).bytes[0]) && \
    ((a).bytes[1] == (b).bytes[1]) && \
    ((a).bytes[2] == (b).bytes[2]) && \
    ((a).bytes[3] == (b).bytes[3])\
)
#define vm_equal64(a, b) (\
    ((a).bytes[0] == (b).bytes[0]) && \
    ((a).bytes[1] == (b).bytes[1]) && \
    ((a).bytes[2] == (b).bytes[2]) && \
    ((a).bytes[3] == (b).bytes[3]) && \
    ((a).bytes[4] == (b).bytes[4]) && \
    ((a).bytes[5] == (b).bytes[5]) && \
    ((a).bytes[6] == (b).bytes[6]) && \
    ((a).bytes[7] == (b).bytes[7])\
)
#define vm_equal128(a, b) (\
    ((a).bytes[0] == (b).bytes[0]) && \
    ((a).bytes[1] == (b).bytes[1]) && \
    ((a).bytes[2] == (b).bytes[2]) && \
    ((a).bytes[3] == (b).bytes[3]) && \
    ((a).bytes[4] == (b).bytes[4]) && \
    ((a).bytes[5] == (b).bytes[5]) && \
    ((a).bytes[6] == (b).bytes[6]) && \
    ((a).bytes[7] == (b).bytes[7]) && \
    ((a).bytes[8] == (b).bytes[8]) && \
    ((a).bytes[9] == (b).bytes[9]) && \
    ((a).bytes[10] == (b).bytes[10]) && \
    ((a).bytes[11] == (b).bytes[11]) && \
    ((a).bytes[12] == (b).bytes[12]) && \
    ((a).bytes[13] == (b).bytes[13]) && \
    ((a).bytes[14] == (b).bytes[14]) && \
    ((a).bytes[15] == (b).bytes[15])\
)
#define vm_equal256(a, b) (\
    ((a).bytes[0] == (b).bytes[0]) && \
    ((a).bytes[1] == (b).bytes[1]) && \
    ((a).bytes[2] == (b).bytes[2]) && \
    ((a).bytes[3] == (b).bytes[3]) && \
    ((a).bytes[4] == (b).bytes[4]) && \
    ((a).bytes[5] == (b).bytes[5]) && \
    ((a).bytes[6] == (b).bytes[6]) && \
    ((a).bytes[7] == (b).bytes[7]) && \
    ((a).bytes[8] == (b).bytes[8]) && \
    ((a).bytes[9] == (b).bytes[9]) && \
    ((a).bytes[10] == (b).bytes[10]) && \
    ((a).bytes[11] == (b).bytes[11]) && \
    ((a).bytes[12] == (b).bytes[12]) && \
    ((a).bytes[13] == (b).bytes[13]) && \
    ((a).bytes[14] == (b).bytes[14]) && \
    ((a).bytes[15] == (b).bytes[15]) && \
    ((a).bytes[16] == (b).bytes[16]) && \
    ((a).bytes[17] == (b).bytes[17]) && \
    ((a).bytes[18] == (b).bytes[18]) && \
    ((a).bytes[19] == (b).bytes[19]) && \
    ((a).bytes[20] == (b).bytes[20]) && \
    ((a).bytes[21] == (b).bytes[21]) && \
    ((a).bytes[22] == (b).bytes[22]) && \
    ((a).bytes[23] == (b).bytes[23]) && \
    ((a).bytes[24] == (b).bytes[24]) && \
    ((a).bytes[25] == (b).bytes[25]) && \
    ((a).bytes[26] == (b).bytes[26]) && \
    ((a).bytes[27] == (b).bytes[27]) && \
    ((a).bytes[28] == (b).bytes[28]) && \
    ((a).bytes[29] == (b).bytes[29]) && \
    ((a).bytes[30] == (b).bytes[30]) && \
    ((a).bytes[31] == (b).bytes[31])\
)

#define vm_not_equal16(a, b) (\
    ((a).bytes[0] != (b).bytes[0]) || \
    ((a).bytes[1] != (b).bytes[1])\
)
#define vm_not_equal32(a, b) (\
    ((a).bytes[0] != (b).bytes[0]) || \
    ((a).bytes[1] != (b).bytes[1]) || \
    ((a).bytes[2] != (b).bytes[2]) || \
    ((a).bytes[3] != (b).bytes[3])\
)
#define vm_not_equal64(a, b) (\
    ((a).bytes[0] != (b).bytes[0]) || \
    ((a).bytes[1] != (b).bytes[1]) || \
    ((a).bytes[2] != (b).bytes[2]) || \
    ((a).bytes[3] != (b).bytes[3]) || \
    ((a).bytes[4] != (b).bytes[4]) || \
    ((a).bytes[5] != (b).bytes[5]) || \
    ((a).bytes[6] != (b).bytes[6]) || \
    ((a).bytes[7] != (b).bytes[7])\
)
#define vm_not_equal128(a, b) (\
    ((a).bytes[0] != (b).bytes[0]) || \
    ((a).bytes[1] != (b).bytes[1]) || \
    ((a).bytes[2] != (b).bytes[2]) || \
    ((a).bytes[3] != (b).bytes[3]) || \
    ((a).bytes[4] != (b).bytes[4]) || \
    ((a).bytes[5] != (b).bytes[5]) || \
    ((a).bytes[6] != (b).bytes[6]) || \
    ((a).bytes[7] != (b).bytes[7]) || \
    ((a).bytes[8] != (b).bytes[8]) || \
    ((a).bytes[9] != (b).bytes[9]) || \
    ((a).bytes[10] != (b).bytes[10]) || \
    ((a).bytes[11] != (b).bytes[11]) || \
    ((a).bytes[12] != (b).bytes[12]) || \
    ((a).bytes[13] != (b).bytes[13]) || \
    ((a).bytes[14] != (b).bytes[14]) || \
    ((a).bytes[15] != (b).bytes[15])\
)
#define vm_not_equal256(a, b) (\
    ((a).bytes[0] != (b).bytes[0]) || \
    ((a).bytes[1] != (b).bytes[1]) || \
    ((a).bytes[2] != (b).bytes[2]) || \
    ((a).bytes[3] != (b).bytes[3]) || \
    ((a).bytes[4] != (b).bytes[4]) || \
    ((a).bytes[5] != (b).bytes[5]) || \
    ((a).bytes[6] != (b).bytes[6]) || \
    ((a).bytes[7] != (b).bytes[7]) || \
    ((a).bytes[8] != (b).bytes[8]) || \
    ((a).bytes[9] != (b).bytes[9]) || \
    ((a).bytes[10] != (b).bytes[10]) || \
    ((a).bytes[11] != (b).bytes[11]) || \
    ((a).bytes[12] != (b).bytes[12]) || \
    ((a).bytes[13] != (b).bytes[13]) || \
    ((a).bytes[14] != (b).bytes[14]) || \
    ((a).bytes[15] != (b).bytes[15]) || \
    ((a).bytes[16] != (b).bytes[16]) || \
    ((a).bytes[17] != (b).bytes[17]) || \
    ((a).bytes[18] != (b).bytes[18]) || \
    ((a).bytes[19] != (b).bytes[19]) || \
    ((a).bytes[20] != (b).bytes[20]) || \
    ((a).bytes[21] != (b).bytes[21]) || \
    ((a).bytes[22] != (b).bytes[22]) || \
    ((a).bytes[23] != (b).bytes[23]) || \
    ((a).bytes[24] != (b).bytes[24]) || \
    ((a).bytes[25] != (b).bytes[25]) || \
    ((a).bytes[26] != (b).bytes[26]) || \
    ((a).bytes[27] != (b).bytes[27]) || \
    ((a).bytes[28] != (b).bytes[28]) || \
    ((a).bytes[29] != (b).bytes[29]) || \
    ((a).bytes[30] != (b).bytes[30]) || \
    ((a).bytes[31] != (b).bytes[31])\
)

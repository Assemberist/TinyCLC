#pragma once
#include "vm256_stdint.h"

#define VM_STACK_SIZE 8192

/////////////////////////////////////////
//              REGISTERS
/////////////////////////////////////////

typedef vm_uint8_t vm_r8;

typedef struct vm_r16{
    vm_r8 sub_r0;
    vm_r8 sub_r1;
} vm_r16;

typedef struct vm_r32{
    vm_r16 sub_r0;
    vm_r16 sub_r1;
} vm_r32;

typedef struct vm_r64{
    vm_r32 sub_r0;
    vm_r32 sub_r1;
} vm_r64;

typedef struct vm_r128{
    vm_r64 sub_r0;
    vm_r64 sub_r1;
} vm_r128;

typedef struct vm_r256{
    vm_r128 sub_r0;
    vm_r128 sub_r1;
} vm_r256;


/////////////////////////////////////////
//               VM BASE
/////////////////////////////////////////

typedef struct VMInstance{
    // registers
    vm_r256 r0, r1, r2, r3;
    vm_r256 rsp256, rsp128, rsp64, rsp32, rsp16, rsp8;
    vm_r256 rip;

    // stacks
    vm_uint256_t stack256[VM_STACK_SIZE / 32];
    vm_uint128_t stack128[VM_STACK_SIZE / 16];
    vm_uint64_t stack64[VM_STACK_SIZE / 8];
    vm_uint32_t stack32[VM_STACK_SIZE / 4];
    vm_uint16_t stack16[VM_STACK_SIZE / 2];
    vm_uint8_t stack8[VM_STACK_SIZE];
} VMInstance;


#define VM_R8(reg, vm) ((vm_uint8_t*)&(vm).r0)[reg % 128]
#define VM_R16(reg, vm) ((vm_uint16_t*)&(vm).r0)[reg % 64]
#define VM_R32(reg, vm) ((vm_uint32_t*)&(vm).r0)[reg % 32]
#define VM_R64(reg, vm) ((vm_uint64_t*)&(vm).r0)[reg % 16]
#define VM_R128(reg, vm) ((vm_uint128_t*)&(vm).r0)[reg % 8]
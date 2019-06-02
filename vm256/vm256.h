#pragma once
#include "vm256_stdint.h"

#define VM_STACK_SIZE 8192
#define VM_IDT_SIZE 1024
#define VM_ID_EXT_SIZE 1024

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
    vm_uint256_t rsp256, rsp128, rsp64, rsp32, rsp16, rsp8;
    vm_uint256_t rip;
    vm_bool halt;

    // stacks
    vm_uint256_t stack256[VM_STACK_SIZE / 32];
    vm_uint128_t stack128[VM_STACK_SIZE / 16];
    vm_uint64_t stack64[VM_STACK_SIZE / 8];
    vm_uint32_t stack32[VM_STACK_SIZE / 4];
    vm_uint16_t stack16[VM_STACK_SIZE / 2];
    vm_uint8_t stack8[VM_STACK_SIZE];
} VMInstance;

#define VMInstanceDefault (VMInstance){\
    .rip = {\
        0x00, 0x00, 0x00, 0x00,\
        0x00, 0x00, 0x00, 0x00,\
        0x00, 0x00, 0x00, 0x00,\
        0x00, 0x00, 0x00, 0x00,\
        0x00, 0x00, 0x00, 0x00,\
        0x00, 0x00, 0x00, 0x00,\
        0x00, 0x00, 0x00, 0x00,\
        0x00, 0x00, 0x00, 0x00\
    },\
    .halt = false\
};


// register macros
#define VM_R8_COUNT 128
#define VM_R16_COUNT 64
#define VM_R32_COUNT 32
#define VM_R64_COUNT 16
#define VM_R128_COUNT 8
#define VM_R256_COUNT 4

#define VM_R8_START 0
#define VM_R16_START VM_R8_COUNT
#define VM_R32_START VM_R8_COUNT + VM_R16_COUNT
#define VM_R64_START VM_R8_COUNT + VM_R16_COUNT + VM_R32_COUNT
#define VM_R128_START VM_R8_COUNT + VM_R16_COUNT + VM_R32_COUNT + VM_R64_COUNT
#define VM_R256_START VM_R8_COUNT + VM_R16_COUNT + VM_R32_COUNT + VM_R64_COUNT + VM_R128_COUNT

#define VM_R8_END VM_R8_START + VM_R8_COUNT
#define VM_R16_END VM_R16_START + VM_R16_COUNT
#define VM_R32_END VM_R32_START + VM_R32_COUNT
#define VM_R64_END VM_R64_START + VM_R64_COUNT
#define VM_R128_END VM_R128_START + VM_R128_COUNT
#define VM_R256_END VM_R256_START + VM_R256_COUNT

#define VM_R8_INDEX_INBOUNDS(index) ((index >= VM_R8_START) && (index < VM_R8_END))
#define VM_R16_INDEX_INBOUNDS(index) ((index >= VM_R16_START) && (index < VM_R16_END))
#define VM_R32_INDEX_INBOUNDS(index) ((index >= VM_R32_START) && (index < VM_R32_END))
#define VM_R64_INDEX_INBOUNDS(index) ((index >= VM_R64_START) && (index < VM_R64_END))
#define VM_R128_INDEX_INBOUNDS(index) ((index >= VM_R128_START) && (index < VM_R128_END))
#define VM_R256_INDEX_INBOUNDS(index) ((index >= VM_R256_START) && (index < VM_R256_END))


#define VM_R8(reg, vm) ((vm_r8*)&(vm).r0)[(reg) % VM_R8_COUNT]
#define VM_R16(reg, vm) ((vm_r16*)&(vm).r0)[(reg) % VM_R16_COUNT]
#define VM_R32(reg, vm) ((vm_r32*)&(vm).r0)[(reg) % VM_R32_COUNT]
#define VM_R64(reg, vm) ((vm_r64*)&(vm).r0)[(reg) % VM_R64_COUNT]
#define VM_R128(reg, vm) ((vm_r128*)&(vm).r0)[(reg) % VM_R128_COUNT]
#define VM_R256(reg, vm) ((vm_r256*)&(vm).r0)[(reg) % VM_R256_COUNT]


// Instruction
typedef enum _VM_INSTRUCTION_TYPE {FREE, SINGLE, DOUBLE, TRIPLE} VM_INSTRUCTION_TYPE;
typedef enum _VM_OPERAND_TYPE {REGISTER, NUMBER, ADDRESS} VM_OPERAND_TYPE;
typedef enum _VM_OPERAND_SIZE{
    UINT8_T = 1, UINT16_T = 2,
    UINT32_T = 4, UINT64_T = 8,
    UINT128_T = 16, UINT256_T = 32
} VM_OPERAND_SIZE;


#define VM_FREE_IMPL(impl) (((void(*)(VMInstance*))(impl)))
#define VM_SINGLE_IMPL(impl) (((void(*)(const void*, VMInstance*))(impl)))
#define VM_DOUBLE_IMPL(impl) (((void(*)(const void*, const void*, VMInstance*))(impl)))
#define VM_TRIPLE_IMPL(impl) (((void(*)(const void*, const void*, const void*, VMInstance*))(impl)))


typedef struct VMInstructionDescriptor{
    const VM_INSTRUCTION_TYPE itype;
    const VM_OPERAND_TYPE op0_type, op1_type, op2_type;
    const VM_OPERAND_SIZE op0_size, op1_size, op2_size;
    const vm_uint32_t icode;
    const char* alias;
    const void* impl;
} VMInstructionDescriptor;

typedef struct VMInstructionDescriptorsTable{
    const VMInstructionDescriptor idt[VM_IDT_SIZE];
    vm_size_t size;
} VMInstructionDescriptorsTable;

typedef struct VMInstructionDescriptorsExt{
    VMInstructionDescriptorsTable* ext[VM_ID_EXT_SIZE];
    vm_size_t size;
} VMInstructionDescriptorsExt;


typedef struct VMInstruction{
    const vm_uint32_t* icode;
    const void* op0;
    const void* op1;
    const void* op2;
} VMInstruction;


/////////////////////////////////////////////////////
//       BASE INSTRUCTION SET IMPLEMENTATIONS
/////////////////////////////////////////////////////

/*
    go adr
    go reg256

    snd from_r, to_r
    snd num, r8
    snd num, r16
    snd num, r32
    snd num, r64
    snd num, r128
    snd num, r256

    push8 num
    push16 num
    push32 num
    push64 num
    push128 num
    push256 num
    push8 r8
    push16 r16
    push32 r32
    push64 r64
    push128 r128
    push256 r256

    pop8 r8
    pop16 r16
    pop32 r32
    pop64 r64
    pop128 r128
    pop256 r256
*/

void _vm_go_adr(vm_uint256_t* adr, VMInstance* vm){
    // go adr
    vm->rip = *adr;
}
void _vm_go_r(vm_uint8_t* reg, VMInstance* vm){
    // go r256
    vm_uint8_t _reg = *reg;

    if(VM_R256_INDEX_INBOUNDS(_reg))
        vm->rip = VM_UINT256_T(VM_R256(_reg - 248, *vm));
    else vm->halt = true;
}

void _vm_snd_r_r(vm_uint8_t* reg0, vm_uint8_t* reg1, VMInstance* vm){
    // snd from_r, to_r
    vm_uint8_t _reg0 = *reg0;
    vm_uint8_t _reg1 = *reg1;

    if(VM_R8_INDEX_INBOUNDS(_reg0) && VM_R8_INDEX_INBOUNDS(_reg1))
        VM_R8(_reg1 - VM_R8_END, *vm) = VM_R8(_reg0 - VM_R8_END, *vm);
    else if(VM_R16_INDEX_INBOUNDS(_reg0) && VM_R16_INDEX_INBOUNDS(_reg1))
        VM_R16(_reg1 - VM_R16_END, *vm) = VM_R16(_reg0 - VM_R16_END, *vm);
    else if(VM_R32_INDEX_INBOUNDS(_reg0) && VM_R32_INDEX_INBOUNDS(_reg1))
        VM_R32(_reg1 - VM_R32_END, *vm) = VM_R32(_reg0 - VM_R32_END, *vm);
    else if(VM_R64_INDEX_INBOUNDS(_reg0) && VM_R64_INDEX_INBOUNDS(_reg1))
        VM_R64(_reg1 - VM_R64_END, *vm) = VM_R64(_reg0 - VM_R64_END, *vm);
    else if(VM_R128_INDEX_INBOUNDS(_reg0) && VM_R128_INDEX_INBOUNDS(_reg1))
        VM_R128(_reg1 - VM_R128_END, *vm) = VM_R128(_reg0 - VM_R128_END, *vm);
    else if(VM_R256_INDEX_INBOUNDS(_reg0) && VM_R256_INDEX_INBOUNDS(_reg1))
        VM_R256(_reg1 - VM_R256_END, *vm) = VM_R256(_reg0 - VM_R256_END, *vm);
    else vm->halt = true;
}
void _vm_snd_num_r8(vm_uint8_t* num, vm_uint8_t* reg, VMInstance* vm){
    // snd num, r8
    vm_uint8_t _reg = *reg;

    if(VM_R8_INDEX_INBOUNDS(_reg))
        VM_UINT8_T(VM_R8(*reg - VM_R8_END, *vm)) = *num;
    else vm->halt = true;
}
void _vm_snd_num_r16(vm_uint16_t* num, vm_uint8_t* reg, VMInstance* vm){
    // snd num, r16
    vm_uint8_t _reg = *reg;

    if(VM_R16_INDEX_INBOUNDS(_reg))
        VM_UINT16_T(VM_R16(*reg - VM_R16_END, *vm)) = *num;
    else vm->halt = true;
}
void _vm_snd_num_r32(vm_uint32_t* num, vm_uint8_t* reg, VMInstance* vm){
    // snd num, r32
    vm_uint8_t _reg = *reg;

    if(VM_R32_INDEX_INBOUNDS(_reg))
        VM_UINT32_T(VM_R32(*reg - VM_R32_END, *vm)) = *num;
    else vm->halt = true;
}
void _vm_snd_num_r64(vm_uint64_t* num, vm_uint8_t* reg, VMInstance* vm){
    // snd num, r64
    vm_uint8_t _reg = *reg;

    if(VM_R64_INDEX_INBOUNDS(_reg))
        VM_UINT64_T(VM_R64(*reg - VM_R64_END, *vm)) = *num;
    else vm->halt = true;
}
void _vm_snd_num_r128(vm_uint128_t* num, vm_uint8_t* reg, VMInstance* vm){
    // snd num, r128
    vm_uint8_t _reg = *reg;

    if(VM_R128_INDEX_INBOUNDS(_reg))
        VM_UINT128_T(VM_R128(*reg - VM_R128_END, *vm)) = *num;
    else vm->halt = true;
}
void _vm_snd_num_r256(vm_uint256_t* num, vm_uint8_t* reg, VMInstance* vm){
    // snd num, r256
    vm_uint8_t _reg = *reg;

    if(VM_R256_INDEX_INBOUNDS(_reg))
        VM_UINT256_T(VM_R256(*reg - VM_R256_END, *vm)) = *num;
    else vm->halt = true;
}

void _vm_push8_num(vm_uint8_t* num, VMInstance* vm){
    // push8 num
    vm->stack8[vm_ui256_to_size_t(vm->rsp8)] = *num;
    vm->rsp8 = vm_inc_ui256(vm->rsp8);
}
void _vm_push16_num(vm_uint16_t* num, VMInstance* vm){
    // push16 num
    vm->stack16[vm_ui256_to_size_t(vm->rsp16)] = *num;
    vm->rsp16 = vm_inc_ui256(vm->rsp16);
}
void _vm_push32_num(vm_uint32_t* num, VMInstance* vm){
    // push32 num
    vm->stack32[vm_ui256_to_size_t(vm->rsp32)] = *num;
    vm->rsp32 = vm_inc_ui256(vm->rsp32);
}
void _vm_push64_num(vm_uint64_t* num, VMInstance* vm){
    // push64 num
    vm->stack64[vm_ui256_to_size_t(vm->rsp64)] = *num;
    vm->rsp64 = vm_inc_ui256(vm->rsp64);
}
void _vm_push128_num(vm_uint128_t* num, VMInstance* vm){
    // push128 num
    vm->stack128[vm_ui256_to_size_t(vm->rsp128)] = *num;
    vm->rsp128 = vm_inc_ui256(vm->rsp128);
}
void _vm_push256_num(vm_uint256_t* num, VMInstance* vm){
    // push256 num
    vm->stack256[vm_ui256_to_size_t(vm->rsp256)] = *num;
    vm->rsp256 = vm_inc_ui256(vm->rsp256);
}

void _vm_push8_r(vm_uint8_t* reg, VMInstance* vm){
    // push8 r8
    vm_uint8_t _reg = *reg;

    if(VM_R8_INDEX_INBOUNDS(_reg)){
        vm->stack8[vm_ui256_to_size_t(vm->rsp8)] = VM_UINT8_T(VM_R8(*reg - VM_R8_END, *vm));
        vm->rsp8 = vm_inc_ui256(vm->rsp8);
    }else vm->halt = true;
}
void _vm_push16_r(vm_uint8_t* reg, VMInstance* vm){
    // push16 r16
    vm_uint8_t _reg = *reg;

    if(VM_R16_INDEX_INBOUNDS(_reg)){
        vm->stack16[vm_ui256_to_size_t(vm->rsp16)] = VM_UINT16_T(VM_R16(*reg - VM_R16_END, *vm));
        vm->rsp16 = vm_inc_ui256(vm->rsp16);
    }else vm->halt = true;
}
void _vm_push32_r(vm_uint8_t* reg, VMInstance* vm){
    // push32 r32
    vm_uint8_t _reg = *reg;

    if(VM_R32_INDEX_INBOUNDS(_reg)){
        vm->stack32[vm_ui256_to_size_t(vm->rsp32)] = VM_UINT32_T(VM_R32(*reg - VM_R32_END, *vm));
        vm->rsp32 = vm_inc_ui256(vm->rsp32);
    }else vm->halt = true;
}
void _vm_push64_r(vm_uint8_t* reg, VMInstance* vm){
    // push64 r64
    vm_uint8_t _reg = *reg;

    if(VM_R64_INDEX_INBOUNDS(_reg)){
        vm->stack64[vm_ui256_to_size_t(vm->rsp64)] = VM_UINT64_T(VM_R64(*reg - VM_R64_END, *vm));
        vm->rsp64 = vm_inc_ui256(vm->rsp64);
    }else vm->halt = true;
}
void _vm_push128_r(vm_uint8_t* reg, VMInstance* vm){
    // push128 r128
    vm_uint8_t _reg = *reg;

    if(VM_R128_INDEX_INBOUNDS(_reg)){
        vm->stack128[vm_ui256_to_size_t(vm->rsp128)] = VM_UINT128_T(VM_R128(*reg - VM_R128_END, *vm));
        vm->rsp128 = vm_inc_ui256(vm->rsp128);
    }else vm->halt = true;
}
void _vm_push256_r(vm_uint8_t* reg, VMInstance* vm){
    // push256 r256
    vm_uint8_t _reg = *reg;

    if(VM_R256_INDEX_INBOUNDS(_reg)){
        vm->stack256[vm_ui256_to_size_t(vm->rsp256)] = VM_UINT256_T(VM_R256(*reg - VM_R256_END, *vm));
        vm->rsp256 = vm_inc_ui256(vm->rsp256);
    }else vm->halt = true;
}

void _vm_pop8(vm_uint8_t* reg, VMInstance* vm){
    // pop8 r8
    vm_uint8_t _reg = *reg;

    if(VM_R8_INDEX_INBOUNDS(_reg)){
        vm->rsp8 = vm_dec_ui256(vm->rsp8);
        VM_UINT8_T(VM_R8(*reg - VM_R8_END, *vm)) = vm->stack8[vm_ui256_to_size_t(vm->rsp8)];
    }else vm->halt = true;
}
void _vm_pop16(vm_uint8_t* reg, VMInstance* vm){
    // pop16 r16
    vm_uint8_t _reg = *reg;

    if(VM_R16_INDEX_INBOUNDS(_reg)){
        vm->rsp16 = vm_dec_ui256(vm->rsp16);
        VM_UINT16_T(VM_R16(*reg - VM_R16_END, *vm)) = vm->stack16[vm_ui256_to_size_t(vm->rsp16)];
    }else vm->halt = true;
}
void _vm_pop32(vm_uint8_t* reg, VMInstance* vm){
    // pop32 r32
    vm_uint8_t _reg = *reg;

    if(VM_R32_INDEX_INBOUNDS(_reg)){
        vm->rsp32 = vm_dec_ui256(vm->rsp32);
        VM_UINT32_T(VM_R32(*reg - VM_R32_END, *vm)) = vm->stack32[vm_ui256_to_size_t(vm->rsp32)];
    }else vm->halt = true;
}
void _vm_pop64(vm_uint8_t* reg, VMInstance* vm){
    // pop64 r64
    vm_uint8_t _reg = *reg;

    if(VM_R64_INDEX_INBOUNDS(_reg)){
        vm->rsp64 = vm_dec_ui256(vm->rsp64);
        VM_UINT64_T(VM_R64(*reg - VM_R64_END, *vm)) = vm->stack64[vm_ui256_to_size_t(vm->rsp64)];
    }else vm->halt = true;
}
void _vm_pop128(vm_uint8_t* reg, VMInstance* vm){
    // pop128 r128
    vm_uint8_t _reg = *reg;

    if(VM_R128_INDEX_INBOUNDS(_reg)){
        vm->rsp128 = vm_dec_ui256(vm->rsp128);
        VM_UINT128_T(VM_R128(*reg - VM_R128_END, *vm)) = vm->stack128[vm_ui256_to_size_t(vm->rsp128)];
    }else vm->halt = true;
}
void _vm_pop256(vm_uint8_t* reg, VMInstance* vm){
    // pop256 r256
    vm_uint8_t _reg = *reg;

    if(VM_R256_INDEX_INBOUNDS(_reg)){
        vm->rsp256 = vm_dec_ui256(vm->rsp256);
        VM_UINT256_T(VM_R256(*reg - VM_R256_END, *vm)) = vm->stack256[vm_ui256_to_size_t(vm->rsp256)];
    }else vm->halt = true;
}


/////////////////////////////////////////////////////
//       GLOBAL INSTRUCTION DESCRIPTORS TABLE
/////////////////////////////////////////////////////

VMInstructionDescriptorsTable GIDT = {
    .idt = {
        (VMInstructionDescriptor){
            .itype = SINGLE,
            .op0_type = ADDRESS,
            .op0_size = UINT32_T,
            .icode = {0x00, 0x00, 0x00, 0x01},
            .alias = "go",
            .impl = _vm_go_adr
        },
        (VMInstructionDescriptor){
            .itype = SINGLE,
            .op0_type = REGISTER,
            .op0_size = UINT8_T,
            .icode = {0x00, 0x00, 0x00, 0x02},
            .alias = "go",
            .impl = _vm_go_r
        },
        (VMInstructionDescriptor){
            .itype = DOUBLE,
            .op0_type = REGISTER, .op1_type = REGISTER,
            .op0_size = UINT8_T, .op1_size = UINT8_T,
            .icode = {0x00, 0x00, 0x00, 0x03},
            .alias = "snd",
            .impl = _vm_snd_r_r
        },
        (VMInstructionDescriptor){
            .itype = DOUBLE,
            .op0_type = NUMBER, .op1_type = REGISTER,
            .op0_size = UINT8_T, .op1_size = UINT8_T,
            .icode = {0x00, 0x00, 0x00, 0x04},
            .alias = "snd",
            .impl = _vm_snd_num_r8
        },
        (VMInstructionDescriptor){
            .itype = DOUBLE,
            .op0_type = NUMBER, .op1_type = REGISTER,
            .op0_size = UINT16_T, .op1_size = UINT8_T,
            .icode = {0x00, 0x00, 0x00, 0x05},
            .alias = "snd",
            .impl = _vm_snd_num_r16
        },
        (VMInstructionDescriptor){
            .itype = DOUBLE,
            .op0_type = NUMBER, .op1_type = REGISTER,
            .op0_size = UINT32_T, .op1_size = UINT8_T,
            .icode = {0x00, 0x00, 0x00, 0x06},
            .alias = "snd",
            .impl = _vm_snd_num_r32
        },
        (VMInstructionDescriptor){
            .itype = DOUBLE,
            .op0_type = NUMBER, .op1_type = REGISTER,
            .op0_size = UINT64_T, .op1_size = UINT8_T,
            .icode = {0x00, 0x00, 0x00, 0x07},
            .alias = "snd",
            .impl = _vm_snd_num_r64
        },
        (VMInstructionDescriptor){
            .itype = DOUBLE,
            .op0_type = NUMBER, .op1_type = REGISTER,
            .op0_size = UINT128_T, .op1_size = UINT8_T,
            .icode = {0x00, 0x00, 0x00, 0x08},
            .alias = "snd",
            .impl = _vm_snd_num_r128
        },
        (VMInstructionDescriptor){
            .itype = DOUBLE,
            .op0_type = NUMBER, .op1_type = REGISTER,
            .op0_size = UINT256_T, .op1_size = UINT8_T,
            .icode = {0x00, 0x00, 0x00, 0x09},
            .alias = "snd",
            .impl = _vm_snd_num_r256
        },
        (VMInstructionDescriptor){
            .itype = SINGLE,
            .op0_type = NUMBER,
            .op0_size = UINT8_T,
            .icode = {0x00, 0x00, 0x00, 0x0a},
            .alias = "push8",
            .impl = _vm_push8_num
        },
        (VMInstructionDescriptor){
            .itype = SINGLE,
            .op0_type = NUMBER,
            .op0_size = UINT16_T,
            .icode = {0x00, 0x00, 0x00, 0x0b},
            .alias = "push16",
            .impl = _vm_push16_num
        },
        (VMInstructionDescriptor){
            .itype = SINGLE,
            .op0_type = NUMBER,
            .op0_size = UINT32_T,
            .icode = {0x00, 0x00, 0x00, 0x0c},
            .alias = "push32",
            .impl = _vm_push32_num
        },
        (VMInstructionDescriptor){
            .itype = SINGLE,
            .op0_type = NUMBER,
            .op0_size = UINT64_T,
            .icode = {0x00, 0x00, 0x00, 0x0d},
            .alias = "push64",
            .impl = _vm_push64_num
        },
        (VMInstructionDescriptor){
            .itype = SINGLE,
            .op0_type = NUMBER,
            .op0_size = UINT128_T,
            .icode = {0x00, 0x00, 0x00, 0x0e},
            .alias = "push128",
            .impl = _vm_push128_num
        },
        (VMInstructionDescriptor){
            .itype = SINGLE,
            .op0_type = NUMBER,
            .op0_size = UINT256_T,
            .icode = {0x00, 0x00, 0x00, 0x0f},
            .alias = "push256",
            .impl = _vm_push256_num
        },
        (VMInstructionDescriptor){
            .itype = SINGLE,
            .op0_type = REGISTER,
            .op0_size = UINT8_T,
            .icode = {0x00, 0x00, 0x00, 0x10},
            .alias = "push8",
            .impl = _vm_push8_r
        },
        (VMInstructionDescriptor){
            .itype = SINGLE,
            .op0_type = REGISTER,
            .op0_size = UINT8_T,
            .icode = {0x00, 0x00, 0x00, 0x11},
            .alias = "push16",
            .impl = _vm_push16_r
        },
        (VMInstructionDescriptor){
            .itype = SINGLE,
            .op0_type = REGISTER,
            .op0_size = UINT8_T,
            .icode = {0x00, 0x00, 0x00, 0x12},
            .alias = "push32",
            .impl = _vm_push32_r
        },
        (VMInstructionDescriptor){
            .itype = SINGLE,
            .op0_type = REGISTER,
            .op0_size = UINT8_T,
            .icode = {0x00, 0x00, 0x00, 0x13},
            .alias = "push64",
            .impl = _vm_push64_r
        },
        (VMInstructionDescriptor){
            .itype = SINGLE,
            .op0_type = REGISTER,
            .op0_size = UINT8_T,
            .icode = {0x00, 0x00, 0x00, 0x14},
            .alias = "push128",
            .impl = _vm_push128_r
        },
        (VMInstructionDescriptor){
            .itype = SINGLE,
            .op0_type = REGISTER,
            .op0_size = UINT8_T,
            .icode = {0x00, 0x00, 0x00, 0x15},
            .alias = "push256",
            .impl = _vm_push256_r
        },
        (VMInstructionDescriptor){
            .itype = SINGLE,
            .op0_type = REGISTER,
            .op0_size = UINT8_T,
            .icode = {0x00, 0x00, 0x00, 0x16},
            .alias = "pop8",
            .impl = _vm_pop8
        },
        (VMInstructionDescriptor){
            .itype = SINGLE,
            .op0_type = REGISTER,
            .op0_size = UINT8_T,
            .icode = {0x00, 0x00, 0x00, 0x17},
            .alias = "pop16",
            .impl = _vm_pop16
        },
        (VMInstructionDescriptor){
            .itype = SINGLE,
            .op0_type = REGISTER,
            .op0_size = UINT8_T,
            .icode = {0x00, 0x00, 0x00, 0x18},
            .alias = "pop32",
            .impl = _vm_pop32
        },
        (VMInstructionDescriptor){
            .itype = SINGLE,
            .op0_type = REGISTER,
            .op0_size = UINT8_T,
            .icode = {0x00, 0x00, 0x00, 0x19},
            .alias = "pop64",
            .impl = _vm_pop64
        },
        (VMInstructionDescriptor){
            .itype = SINGLE,
            .op0_type = REGISTER,
            .op0_size = UINT8_T,
            .icode = {0x00, 0x00, 0x00, 0x1A},
            .alias = "pop128",
            .impl = _vm_pop128
        },
        (VMInstructionDescriptor){
            .itype = SINGLE,
            .op0_type = REGISTER,
            .op0_size = UINT8_T,
            .icode = {0x00, 0x00, 0x00, 0x1B},
            .alias = "pop256",
            .impl = _vm_pop256
        }
    },
    .size = 27
};


/////////////////////////////////////////
//               METHODS
/////////////////////////////////////////
const VMInstructionDescriptor* _vmFindInstructionIDT(const vm_uint32_t* icode, VMInstructionDescriptorsTable* idt){
    vm_size_t size = idt->size;

    for(vm_size_t i = 0; i < size; i++){
        if(vm_equal_ui32(*icode, idt->idt[i].icode)) return idt->idt + i;
    }    
    return NULL;
}
const VMInstructionDescriptor* vmFindInstruction(const vm_uint32_t* icode, VMInstructionDescriptorsExt* ext){
    const VMInstructionDescriptor* desc = _vmFindInstructionIDT(icode, &GIDT);
    if(desc != NULL) return desc;

    if(ext != NULL){
        for(vm_size_t i = 0; i < ext->size; i++){
            desc = _vmFindInstructionIDT(icode, ext->ext[i]);
            if(desc != NULL) return desc;
        }
    }

    return NULL;
}

void vmExecInstruction(VMInstruction* instr, VMInstance* vm, VMInstructionDescriptorsExt* ext){
    if(vm->halt == false){
        const VMInstructionDescriptor* desc = vmFindInstruction(instr->icode, ext);

        if(desc != NULL){
            switch (desc->itype){
            case FREE:
                VM_FREE_IMPL(desc->impl)(vm);
                break;
            case SINGLE:
                VM_SINGLE_IMPL(desc->impl)(instr->op0, vm);
                break;
            case DOUBLE:
                VM_DOUBLE_IMPL(desc->impl)(instr->op0, instr->op1, vm);
                break;
            case TRIPLE:
                VM_TRIPLE_IMPL(desc->impl)(instr->op0, instr->op1, instr->op2, vm);
                break;
            default:
                break;
            }
        }
    }else ; // do some exception here
}
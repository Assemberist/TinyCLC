#pragma once
#include "vm256_stdint.h"

#define VM_STACK_SIZE 8192
#define VM_IDT_SIZE 1024

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
    size_t size;
} VMInstructionDescriptorsTable;


typedef struct VMInstruction{
    const vm_uint32_t* icode;
    const void* op0;
    const void* op1;
    const void* op2;
} VMInstruction;


/////////////////////////////////////////////////////
//       BASE INSTRUCTION SET IMPLEMENTATIONS
/////////////////////////////////////////////////////

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
        }
    },
    .size = 9
};


/////////////////////////////////////////
//               METHODS
/////////////////////////////////////////
const VMInstructionDescriptor* _vmFindInstructionIDT(const vm_uint32_t* icode, VMInstructionDescriptorsTable* extra){
    size_t size = extra->size;

    for(size_t i = 0; i < size; i++){
        if(vm_equal32(*icode, extra->idt[i].icode)) return extra->idt + i;
    }    
    return NULL;
}
const VMInstructionDescriptor* vmFindInstruction(const vm_uint32_t* icode, VMInstructionDescriptorsTable* extra){
    const VMInstructionDescriptor* desc = _vmFindInstructionIDT(icode, &GIDT);
    if(desc != NULL) return desc;

    if(extra != NULL){
        desc = _vmFindInstructionIDT(icode, extra);
        if(desc != NULL) return desc;
    }

    return NULL;
}

void vmExecInstruction(VMInstruction* instr, VMInstance* vm, VMInstructionDescriptorsTable* extra){
    if(vm->halt == false){
        const VMInstructionDescriptor* desc = vmFindInstruction(instr->icode, extra);

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
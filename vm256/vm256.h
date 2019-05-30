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


// reference to register
#define VM_R8(reg, vm) ((vm_r8*)&(vm).r0)[(reg) % 128]
#define VM_R16(reg, vm) ((vm_r16*)&(vm).r0)[(reg) % 64]
#define VM_R32(reg, vm) ((vm_r32*)&(vm).r0)[(reg) % 32]
#define VM_R64(reg, vm) ((vm_r64*)&(vm).r0)[(reg) % 16]
#define VM_R128(reg, vm) ((vm_r128*)&(vm).r0)[(reg) % 8]
#define VM_R256(reg, vm) ((vm_r256*)&(vm).r0)[(reg) % 4]


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
    if(_reg >= 248)
        vm->rip = VM_UINT256_T(VM_R256(_reg - 248, *vm));
    else vm->halt = true;
}

void _vm_snd_r_r(vm_uint8_t* reg0, vm_uint8_t* reg1, VMInstance* vm){
    // snd from_r, to_r
    vm_uint8_t _reg0 = *reg0;
    vm_uint8_t _reg1 = *reg1;

    if(_reg0 < 128){

    }else if(_reg0 < 128 + 64){

    }else if(_reg0 < 128 + 64 + 32){

    }else if(_reg0 < 128 + 64 + 32 + 16){

    }else if(_reg0 < 128 + 64 + 32 + 16 + 8){

    }else if(_reg0 < 128 + 64 + 32 + 16 + 8 + 4){

    } else vm->halt = true;
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
        }
    },
    .size = 3
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
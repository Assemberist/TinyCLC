#include "stdio.h"

#define VM_TARGET_ARCH64
#include "vm256.h"


int main(){
    VMInstance vm = VMInstanceDefault;

    // snd 0x12310743ff7394171181448956732301, r128_0

    // bytecode
    vm_uint32_t icode = {0x00, 0x00, 0x00, 0x08};
    vm_uint128_t op0 = {
        0x12, 0x31, 0x07, 0x43,
        0xff, 0x73, 0x94, 0x17,
        0x11, 0x81, 0x44, 0x89,
        0x56, 0x73, 0x23, 0x01
    };
    vm_uint8_t op1 = 240;


    // instructions
    VMInstruction i = {
        .icode = &icode,
        .op0 = &op0,
        .op1 = &op1
    };

    vmExecInstruction(&i, &vm, NULL);

    if(vm.halt)
        printf("Wrong instruction! VMInstance %p halted\n", &vm);

    return 0;
}
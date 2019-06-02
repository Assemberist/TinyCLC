#include "stdio.h"

#define VM_TARGET_ARCH64
#include "vm256.h"



int main(){
    // VMInstance vm = VMInstanceDefault;
    // vm.stack8[0] = 4;
    // vm.rsp8 = vm_inc_ui256(vm.rsp8);

    // // bytecode
    // vm_uint32_t icode = {0x00, 0x00, 0x00, 0x16};
    // vm_uint8_t op = 0;

    // // instructions
    // VMInstruction i = {
    //     .icode = &icode,
    //     .op0 = &op
    // };

    // vmExecInstruction(&i, &vm, NULL);

    // if(vm.halt)
    //     printf("Wrong instruction! VMInstance %p halted\n", &vm);

    vm_uint256_t a = {
        0xa1, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
    };

    vm_uint256_t b = vm_dec_ui256(a);

    return 0;
}
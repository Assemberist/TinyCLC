#include "stdio.h"

#define VM_TARGET_ARCH64
#include "vm256.h"



int main(){
    // VMInstance vm = VMInstanceDefault;

    // // bytecode
    // vm_uint32_t icode = {0x00, 0x00, 0x00, 0x0A};
    // vm_uint8_t op = 4;

    // // instructions
    // VMInstruction i = {
    //     .icode = &icode,
    //     .op0 = &op
    // };

    // vmExecInstruction(&i, &vm, NULL);

    // if(vm.halt)
    //     printf("Wrong instruction! VMInstance %p halted\n", &vm);

    vm_uint32_t a = {
        0x00, 0x00, 0x00, 0x00
    };

    vm_uint32_t b = vm_inc_ui32(a);

    return 0;
}
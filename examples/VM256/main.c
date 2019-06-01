#include "stdio.h"

#define VM_TARGET_ARCH64
#include "vm256.h"



int main(){
    // VMInstance vm = VMInstanceDefault;

    // // bytecode
    // vm_uint32_t icode = {0x00, 0x00, 0x00, 0xA0};

    // // instructions
    // VMInstruction i = {
    //     .icode = &icode
    // };

    // vmExecInstruction(&i, &vm, NULL);

    // if(vm.halt)
    //     printf("Wrong instruction! VMInstance %p halted\n", &vm);

    vm_uint128_t _a = {0xfe, 0x21, 0x30, 0xaa, 0xfe, 0x31, 0x3b, 0x04, 0xff, 0x01, 0xa0, 0x22, 0xee, 0x11, 0x3a, 0x01};

    vm_size_t a = 0xff01a022ee113a01;
    vm_size_t b = vm_ui128_to_size_t(_a);

    printf("%d %d\n", a, b);

    return 0;
}
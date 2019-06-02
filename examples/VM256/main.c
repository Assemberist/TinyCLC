#include "stdio.h"

#define VM_TARGET_ARCH64
#include "vm256.h"



int main(){
    VMInstance vm = VMInstanceDefault;
    vm.stack256[0] = (vm_uint256_t){
        0xa0, 0x04, 0x11, 0x0a,
        0xa0, 0x04, 0x11, 0x0a,
        0xa0, 0x04, 0x11, 0x0a,
        0xa0, 0x04, 0x11, 0x0a,
        0xa0, 0x04, 0x11, 0x0a,
        0xa0, 0x04, 0x11, 0x0a,
        0xa0, 0x04, 0x11, 0x0a,
        0xa0, 0x04, 0x11, 0x0a,
    };
    vm.rsp256 = vm_inc_ui256(vm.rsp256);

    // bytecode
    vm_uint32_t icode = {0x00, 0x00, 0x00, 0x1B};
    vm_uint8_t op = VM_R256_START;

    // instructions
    VMInstruction i = {
        .icode = &icode,
        .op0 = &op
    };

    vmExecInstruction(&i, &vm, NULL);

    if(vm.halt)
        printf("Wrong instruction! VMInstance %p halted\n", &vm);

    return 0;
}
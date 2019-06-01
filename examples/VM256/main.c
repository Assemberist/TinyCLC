#include "stdio.h"

#define VM_TARGET_ARCH64
#include "vm256.h"



int main(){
    VMInstance vm = VMInstanceDefault;
    VM_UINT256_T(VM_R256(0, vm)) = (vm_uint256_t){
        0x0a, 0x03, 0x11, 0xff,
        0x0a, 0x03, 0x11, 0xff,
        0x0a, 0x03, 0x11, 0xff,
        0x0a, 0x03, 0x11, 0xff,
        0x0a, 0x03, 0x11, 0xff,
        0x0a, 0x03, 0x11, 0xff,
        0x0a, 0x03, 0x11, 0xff,
        0x0a, 0x03, 0x11, 0xff
    };

    // bytecode
    vm_uint32_t icode = {0x00, 0x00, 0x00, 0x15};
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
#include "stdio.h"

#define VM_TARGET_ARCH64
#include "vm256.h"


int main(){
    VMInstance vm = VMInstanceDefault;
    VM_R8(31, vm) = 1;

    // snd r16_0, r8_0 (wrong instruction)

    // bytecode
    vm_uint32_t icode = {0x00, 0x00, 0x00, 0x03};
    vm_uint8_t op0 = 128;
    vm_uint8_t op1 = 0;

    // vm_uint256_t op = {
    //     0x00, 0x00, 0x00, 0x00,
    //     0x00, 0x00, 0x00, 0x00,
    //     0x00, 0x00, 0x00, 0x00,
    //     0x00, 0x00, 0x00, 0x00,
    //     0x00, 0x00, 0x00, 0x00,
    //     0x00, 0x00, 0x00, 0x00,
    //     0x00, 0x00, 0x00, 0x00,
    //     0x00, 0x00, 0x00, 0x02,
    // };

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
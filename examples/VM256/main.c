#include "stdio.h"

#define VM_TARGET_ARCH64
#include "vm256.h"



int main(){
    VMInstance vm = VMInstanceDefault;

    // assembly
    /*
        push8 14
        pop8 r8_0
    */

    // bytecode
    vm_uint32_t icode0 = {0x00, 0x00, 0x00, 0x0a};
    vm_uint8_t op0 = 14;

    vm_uint32_t icode1 = {0x00, 0x00, 0x00, 0x16};
    vm_uint8_t op1 = 0;


    // program
    VMProgram prog = {
        .program = {
            (VMInstruction){
                .icode = &icode0,
                .op0 = &op0
            },
            (VMInstruction){
                .icode = &icode1,
                .op0 = &op1
            }
        },
        .size = 2
    };
    
    vmExecProgram(&prog, &vm, NULL);

    if(vm.halt)
        printf("Wrong instruction! VMInstance %p halted\n", &vm);

    return 0;
}
#include "stdio.h"

#define VM_TARGET_ARCH64
#include "vm256.h"



int main(){
    VMInstance vm = VMInstanceDefault;

    // program
    /*
        rip: assembly   ; bytecode
        0  : push8 14   ; 0x0000000a 0x0e
        1  : pop8 r8_0  ; 0x00000016 0x00
    */

    vm_uint8_t bytecode[10] = {
        0x00, 0x00, 0x00, 0x0a, 0x0e,
        0x00, 0x00, 0x00, 0x16, 0x00
    };


    VMProgram prog = {.size = 2};

    VMParser p = vmParseInstruction(bytecode, &vm, NULL);
    prog.program[0] = p.instr;

    p = vmParseInstruction(p.next, &vm, NULL);
    prog.program[1] = p.instr;

    vmExecProgram(&prog, &vm, NULL);

    if(vm.halt)
        printf("Wrong instruction! VMInstance %p halted\n", &vm);

    return 0;
}
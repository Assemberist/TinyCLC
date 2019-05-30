#include "stdio.h"

#define VM_TARGET_ARCH64
#include "vm256.h"

// extended instruction set test
void my_instr(VMInstance* vm){
    puts("My first ext instruction!");
}

VMInstructionDescriptorsTable my_ext = {
    .idt = {
        (VMInstructionDescriptor){
            .itype = FREE,
            .icode = {0x00, 0x00, 0x00, 0xA0},
            .alias = "myi",
            .impl = my_instr
        }
    },
    .size = 1
};

int main(){
    VMInstance vm = VMInstanceDefault;
    VMInstructionDescriptorsExt ext = {
        .ext = {
            &my_ext
        },
        .size = 1
    };

    // bytecode
    vm_uint32_t icode = {0x00, 0x00, 0x00, 0xA0};

    // instructions
    VMInstruction i = {
        .icode = &icode
    };

    vmExecInstruction(&i, &vm, &ext);

    if(vm.halt)
        printf("Wrong instruction! VMInstance %p halted\n", &vm);

    return 0;
}
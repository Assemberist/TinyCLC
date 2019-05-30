#include "stdio.h"

#define VM_TARGET_ARCH64
#include "vm256.h"

int main(){
    VMInstance vm;

    VM_R8(2, vm) = 4;

    return 0;
}
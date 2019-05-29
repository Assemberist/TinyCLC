#include "stdio.h"

#define VM_TARGET_ARCH64
#include "vm256.h"

int main(){
    vm_uint16_t a = {0xff, 0x11};
    vm_uint16_t b = {0xff, 0x11};

    vm_bool c = vm_not_equal16(a, b);

    return 0;
}
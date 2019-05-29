#include "stdio.h"

#define VM_TARGET_ARCH64
#include "vm256.h"

int main(){
    vm_uint16_t a = {0x00, 0x00};
    vm_uint16_t b = {0xff, 0xff};

    vm_uint16_t c = vm_and_u16(a, b);

    printf("%#02x %#02x\n", c.bytes[0], c.bytes[1]);

    return 0;
}
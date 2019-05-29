#include "stdio.h"

#define VM_TARGET_ARCH64
#include "vm256.h"

int main(){
    vm_uint16_t a = {0xff, 0x11};
    vm_uint8_t b[2] = {0xff, 0x11};

    printf("%#04x %#04x\n", a.bytes[0], a.bytes[1]);
    printf("%#04x %#04x\n", b[0], b[1]);

    return 0;
}
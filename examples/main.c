#include <stdio.h>
#include <time.h>
#include "renderer_ascii.h"

int main(int argc, char* argv[]){
    RdScreen win = rdCreateScreen(41, 13);
    auto viewport = rdCreateViewportIdentity(&win);

    rdClear(&win);
    rdRender(&win);

    rdDestroyScreen(&win);
    return 0;
}
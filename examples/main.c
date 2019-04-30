#include <stdio.h>
#include "renderer_ascii.h"

int main(int argc, char* argv[]){
    // RdScreen window = rdCreateScreen(atol(argv[1]), atol(argv[2]));
    RdScreen window = rdCreateScreen(33, 13);

    RdVertex2f v0 = {0.5f, 0.5f, 1.0f};
    RdVertex3f v1 = {0.5f, 0.5f, 1.5f, 1.0f};
    
    rdClear(&window);
    rdPoint2f(&v0, &window);
    rdPoint3f(&v1, &window);
    // rdLines2f(verts, 2, &window, LINE_LOOP);
    rdRender(&window);

    rdDestroyScreen(&window);
    return 0;
}

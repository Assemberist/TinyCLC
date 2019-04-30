#include <stdio.h>
#include "renderer_ascii.h"


int main(int argc, char* argv[]){
    RdScreen window = rdCreateScreen(atol(argv[1]), atol(argv[2]));
    // RdScreen window = rdCreateScreen(21, 13);

    RdViewport view = {1.0f, 1.0f, 1.0f};
    window.viewport = &view;

    RdVertex2f verts[5] = {
        (RdVertex2f){-0.12f, -0.72f, 0.5f},
        (RdVertex2f){0.75f, -0.25f, 1.0f},
        (RdVertex2f){0.57f, 0.72f, 0.8f},
        (RdVertex2f){-0.41f, 0.85f, 1.0f},
        (RdVertex2f){-0.84f, -0.04f, 0.5f}
    };
    

    rdClear(&window);
    rdLines2f(verts, 5, &window, LINE_LOOP);
    rdRender(&window);

    rdDestroyScreen(&window);
    return 0;
}

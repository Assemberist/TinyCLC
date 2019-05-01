#include <stdio.h>
#include <time.h>
#include "renderer_ascii.h"

void sleep(int);

int main(int argc, char* argv[]){
    size_t w = atol(argv[1]);
    size_t h = atol(argv[2]);

    RdScreen window = rdCreateScreen(w, h);
    // RdScreen window = rdCreateScreen(31, 13);

    RdViewport view = rdCreateViewportIdentity(&window);
    window.viewport = &view;

    RdVertex2f verts[4] = {
        (RdVertex2f){-0.5, 0.5f, 1.0f},
        (RdVertex2f){0.5, 0.5f, 1.0f},
        (RdVertex2f){0.5, -0.5f, 1.0f},
        (RdVertex2f){-0.5, -0.5f, 1.0f}
    };

    rdSetScale2f(0.75f, 0.75f);
    rdSetRotate2f(45.0f);
    rdSetTranslate2f(0.5f, 0.0f);

    rdClear(&window);
    rdLines2f(verts, 4, &window, LINE_LOOP);
    rdRender(&window);


    rdDestroyScreen(&window);
    return 0;
}

void sleep(int ms){
    int milisec = ms;
    struct timespec req = {0};
    req.tv_sec = 0;
    req.tv_nsec = milisec * 1000000L;
    nanosleep(&req, NULL);
}
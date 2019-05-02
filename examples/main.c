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

    const float side = 0.5f;
    const float color = 0.99f;

    RdVertex3f verts[8] = {
        (RdVertex3f){-side, side, -side, color},
        (RdVertex3f){side, side, -side, color},
        (RdVertex3f){-side, side, side, color},
        (RdVertex3f){side, side, side, color},
        (RdVertex3f){-side, -side, -side, color},
        (RdVertex3f){side, -side, -side, color},
        (RdVertex3f){-side, -side, side, color},
        (RdVertex3f){side, -side, side, color},
    };

    RdIndex2 indexes[12] = {
        (RdIndex2){0, 1},
        (RdIndex2){0, 2},
        (RdIndex2){0, 4},
        (RdIndex2){1, 3},
        (RdIndex2){1, 5},
        (RdIndex2){2, 3},
        (RdIndex2){2, 6},
        (RdIndex2){4, 5},
        (RdIndex2){4, 6},
        (RdIndex2){5, 7},
        (RdIndex2){6, 7},
        (RdIndex2){3, 7}
    };

    rdSetTranslate3f(0, 0, 1.5f);

    for(size_t i = 0; i < 640; i++){
        rdSetRotate3f(1, 1, 1, i);

        rdClear(&window);
        rdLines3f(verts, indexes, 12, &window);
        rdDRender(&window);
        sleep(5); //5
    }

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
#include <stdio.h>
#include <time.h>
#include "renderer_ascii.h"

void sleep(int);

int main(int argc, char* argv[]){
    RdScreen window = rdCreateScreen(atol(argv[1]), atol(argv[2]));
    // RdScreen window = rdCreateScreen(31, 13);

    RdViewport view = {1.0f, 1.0f, 1.0f};
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

    rdSetTranslate3f(0, 0, 1.5f);

    for(size_t i = 0; i < 640; i++){
        rdSetRotate3f(1, 1, 0, i);
        rdClear(&window);

        rdLine3f(verts, verts + 1, &window);
        rdLine3f(verts, verts + 2, &window);
        rdLine3f(verts + 1, verts + 3, &window);
        rdLine3f(verts + 2, verts + 3, &window);
        rdLine3f(verts + 4, verts + 5, &window);
        rdLine3f(verts + 4, verts + 6, &window);
        rdLine3f(verts + 5, verts + 7, &window);
        rdLine3f(verts + 6, verts + 7, &window);
        rdLine3f(verts, verts + 4, &window);
        rdLine3f(verts + 1, verts + 5, &window);
        rdLine3f(verts + 2, verts + 6, &window);
        rdLine3f(verts + 3, verts + 7, &window);

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
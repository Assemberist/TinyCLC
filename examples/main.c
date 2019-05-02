#include <stdio.h>
#include <time.h>
#include "renderer_ascii.h"

void sleep(int);

RdVertex2f vShader(RdVertex2f* v){
    RdVertex2f result = rdMat3Mul2f(v, rdScale2f);
    result = rdMat3Mul2f(&result, rdRotate2f);
    result = rdMat3Mul2f(&result, rdTranslate2f);

    return result;
}
float fShader(RdScreenPoint* p, float color){
    return color;
}

int main(int argc, char* argv[]){
    size_t w = atol(argv[1]);
    size_t h = atol(argv[2]);

    RdScreen window = rdCreateScreen(w, h);
    // RdScreen window = rdCreateScreen(31, 13);

    RdViewport view = {1.0f, 1.0f, 1.0f};
    window.viewport = &view;

    RdVertex2f verts[3] = {
        (RdVertex2f){0.0f, 1.0f, 0.25f},
        (RdVertex2f){-1.0f, -1.0f, 0.5f},
        (RdVertex2f){1.0f, -1.0f, 1.0f}
    };
    RdIndex2 indexes[3] = {
        (RdIndex2){0, 1},
        (RdIndex2){0, 2},
        (RdIndex2){1, 2}
    };

    rdSetRotate2f(90.0f);

    rdClear(&window);
    rdLines2f(verts, indexes, 3, vShader, fShader, &window);
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
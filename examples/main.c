#include <stdio.h>
#include <time.h>
#include "renderer_ascii.h"


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

    RdViewport view = rdCreateViewportIdentity(&window);
    // RdViewport view = {1.0f, 1.0f, 1.0f};
    window.viewport = &view;

    // set data
    RdVertex2f verts[] = {
        (RdVertex2f){0.0f, 1.0f, 0.25f},
        (RdVertex2f){-1.0f, -1.0f, 1.0f},
        (RdVertex2f){1.0f, -1.0f, 0.85f}
    };
    RdIndex2 indexes[] = {
        (RdIndex2){0, 1},
        (RdIndex2){0, 2},
        (RdIndex2){1, 2}
    };
    
    RdProgram2f prog = {vShader, fShader};

    rdClear(&window);
    rdLines2f(verts, indexes, 3, &prog, &window);
    rdRender(&window);

    rdDestroyScreen(&window);
    return 0;
}
#include <stdio.h>
#include <time.h>
#include "renderer_ascii.h"


RdVertex3f vShader(RdVertex3f* v){
    RdVertex3f result = rdMat4Mul3f(v, rdScale3f);
    result = rdMat4Mul3f(&result, rdRotate3f);
    result = rdMat4Mul3f(&result, rdTranslate3f);

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
        (RdVertex3f){side, -side, side, color}
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

    RdProgram3f prog = {vShader, fShader};

    rdSetTranslate3f(0.0f, 0.0f, 1.5f);

    for(float i = 0; i < 360; i += 0.1f){
        rdSetRotate3f(0, 1, 0, i);

        rdClear(&window);
        rdLines3f(verts, indexes, 12, &prog, &window);
        rdDRender(&window);
    }

    rdDestroyScreen(&window);
    return 0;
}
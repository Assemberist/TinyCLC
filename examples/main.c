#include <stdio.h>
#include <time.h>
#include "renderer_ascii.h"


RdVertex3 vshader(const RdVertex2* v, RdVertexShader2* shader){
    mat3f_ptr scale = shader->matrices._data[0];
    mat3f_ptr rotation = shader->matrices._data[1];
    mat3f_ptr position = shader->matrices._data[2];

    mat3(float) global = mat3mat3(float)(scale, rotation);
    global = mat3mat3(float)(&global, position);

    vec3(float) temp = mat3vec2(float)(&v->position, &global);

    return (RdVertex3){temp, v->color};
}

float fshader(const vec2(int)* p, RdFragmentShader* shader){
    float color = shader->attributes._data[0];

    return color;
}


int main(int argc, char* argv[]){
    // setup window
    RdScreen win = rdCreateScreen(atol(argv[1]), atol(argv[2]));
    vec3(float) viewport = rdCreateViewportIdentity(&win);
    win.viewport = &viewport;

    // setup geometry
    RdVertex2 verts[3] = {
        (RdVertex2){0.0f, 1.0f, 0.25f},
        (RdVertex2){-1.0f, -1.0f, 0.85f},
        (RdVertex2){1.0f, -1.0f, 1.0f}
    };

    // setup matrices
    mat3(float) transpose = {{
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    }};
    mat3(float) rotate = {{
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    }};
    mat3(float) scale = {{
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    }};

    std_small_vector(mat3f_ptr) pos = std_small_vector_default(mat3f_ptr);
    pos.push_back(&pos, &scale);
    pos.push_back(&pos, &rotate);
    pos.push_back(&pos, &transpose);

    // setup shaders
    RdVertexShader2 vsh = {
        vshader,
        pos
    };
    RdFragmentShader fsh = {
        fshader,
        std_small_vector_default(float)
    };
    fsh.attributes.push_back(&fsh.attributes, 0.0f);

    RdProgram2 prog = {&vsh, &fsh};

    // render
    rdScale2((vec2(float)){0.5f, 0.5f}, &scale);

    for(float i = 0; i < 360; i += 0.1f){
        rdRotate2(i, &rotate);

        rdClear(&win);
        rdPoints2(verts, 3, &prog, &win);
        rdDRender(&win);
    }
    rdRender(&win);

    // free
    rdDestroyScreen(&win);
    return 0;
}
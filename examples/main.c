#include <stdio.h>
#include <time.h>
#include "renderer_ascii.h"


RdVertex3 vshader(const RdVertex2* v, RdVertexShader2* shader){
    mat3f_ptr scale = shader->matrices._data[0];
    mat3f_ptr rotation = shader->matrices._data[1];
    mat3f_ptr position = shader->matrices._data[2];

    mat3(float) global = mat3_mul_mat3(float)(scale, rotation);
    global = mat3_mul_mat3(float)(&global, position);

    vec3(float) temp = mat3_mul_vec3(float)((vec3(float)){v->position.x, v->position.y, 1.0f}, &global);

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
        (RdVertex2){-1.0f, -1.0f, 0.55f},
        (RdVertex2){1.0f, -1.0f, 0.84f}
    };
    vec2(size_t) indexes[3] = {
        (vec2(size_t)){0, 1},
        (vec2(size_t)){1, 2},
        (vec2(size_t)){2, 0}
    };

    // setup matrices
    mat3(float) transpose = mat3_identity(float);
    mat3(float) rotate = mat3_identity(float);
    mat3(float) scale = mat3_identity(float);

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

    for(float i = 0; i < 180; i += 0.05f){
        rdRotate2(i, &rotate);

        rdClear(&win);
        rdTriangle2(verts, verts + 1, verts + 2, &prog, &win);
        // rdLines2(verts, indexes, 3, &prog, &win);
        rdDRender(&win);
    }
    rdRender(&win);

    // free
    rdDestroyScreen(&win);
    return 0;
}
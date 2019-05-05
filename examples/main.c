#include <stdio.h>
#include <time.h>
#include "renderer_ascii.h"


RdVertex4 vshader(const RdVertex3* v, RdVertexShader3* shader){
    mat4f_ptr scale = shader->matrices._data[0];
    mat4f_ptr rotation = shader->matrices._data[1];
    mat4f_ptr position = shader->matrices._data[2];

    mat4(float) global = mat4_mul_mat4(float)(position, rotation);
    global = mat4_mul_mat4(float)(&global, scale);

    vec4(float) temp = mat4_mul_vec4(float)((vec4(float)){v->position.x, v->position.y, v->position.z, 1.0f}, &global);

    return (RdVertex4){temp, v->color};
}

float fshader(const vec2(int)* p, RdFragmentShader* shader){
    float color = shader->attributes._data[0];

    return color;
}


int main(int argc, char* argv[]){
    // setup window
    RdScreen win = rdCreateScreen(atol(argv[1]), atol(argv[2]));
    // RdScreen win = rdCreateScreen(31, 13);
    vec3(float) viewport = rdCreateViewportIdentity(&win);
    win.viewport = &viewport;

    // setup geometry
    RdVertex3 verts[8] = {
        {-1.0f, 1.0f, -1.0f, 0.44f},
        {1.0f, 1.0f, -1.0f, 1.0f},
        {-1.0f, 1.0f, 1.0f, 0.54f},
        {1.0f, 1.0f, 1.0f, 0.91f},
        {-1.0f, -1.0f, -1.0f, 0.1f},
        {1.0f, -1.0f, -1.0f, 0.45f},
        {-1.0f, -1.0f, 1.0f, 1.0f},
        {1.0f, -1.0f, 1.0f, 0.7f}
    };

    vec3(size_t) indexes[12] = {
        {2, 6, 7},
        {7, 3, 2},
        {0, 4, 5},
        {5, 1, 0},

        {0, 4, 6},
        {6, 2, 0},
        {1, 5, 7},
        {7, 3, 1},

        {0, 1, 3},
        {3, 2, 0},
        {4, 5, 7},
        {7, 6, 4}
    };

    vec2(size_t) indexes_lines[12] = {
        {0, 1},
        {0, 2},
        {0, 4},
        {1, 3},
        {1, 5},
        {2, 3},
        {2, 6},
        {3, 7},
        {4, 5},
        {4, 6},
        {5, 7},
        {6, 7}
    };


    // setup matrices
    mat4(float) transpose = mat4_identity(float);
    mat4(float) rotate = mat4_identity(float);
    mat4(float) scale = mat4_identity(float);

    std_small_vector(mat4f_ptr) pos = std_small_vector_default(mat4f_ptr);
    pos.push_back(&pos, &scale);
    pos.push_back(&pos, &rotate);
    pos.push_back(&pos, &transpose);

    // setup shaders
    RdVertexShader3 vsh = {
        vshader,
        pos
    };
    RdFragmentShader fsh = {
        fshader,
        std_small_vector_default(float)
    };
    fsh.attributes.push_back(&fsh.attributes, 0.0f);

    RdProgram3 prog = {&vsh, &fsh};

    // render
    rdTranslate3((vec3(float)){0, 0, 3}, &transpose);

    for(float i = 0; i <= 420; i += 0.1f){
        rdRotate3((vec3(float)){0, 1, 0}, i,  &rotate);

        rdClear(&win);
        // rdLines3(verts, indexes_lines, 12, &prog, &win);
        rdTriangles3(verts, indexes, 12, &prog, &win);
        rdDRender(&win);
    }
    rdRender(&win);

    // free
    rdDestroyScreen(&win);
    return 0;
}
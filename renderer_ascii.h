#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <omp.h>

/////////////////////////////////////////////////////
//                   REQUIRED
/////////////////////////////////////////////////////
#define STD_SMALL_VECTOR_DONT_USE_PREDEFINED_TYPES
#define LINEAR_DONT_USE_PREDEFINED_TYPES
#include "small_vector.h"
#include "linear.h"


LINEAR(float)
LINEAR(double)
LINEAR(int)
LINEAR(size_t)

typedef const mat3(float)* mat3f_ptr;
SMALL_VECTORS(mat3f_ptr);
SMALL_VECTORS(float)

/////////////////////////////////////////////////////
//                     MACROS
/////////////////////////////////////////////////////
#define RD_NORMALIZED_FLOAT_MIN_ZERO(X) if(X < 0.0f) X = 0.0f;\
else if(X > 1.0f) X = 1.0f;

// #define RD_DEBUG
#define RD_SHOW_GRID
// #define RD_WHITE_BACK

/////////////////////////////////////////////////////
//                 DATA STRUCTURES
/////////////////////////////////////////////////////
typedef struct RdVertex2{
    vec2(float) position;
    float color;
} RdVertex2;

typedef struct RdVertex3{
    vec3(float) position;
    float color;
} RdVertex3;

typedef struct RdVertex4{
    vec4(float) position;
    float color;
} RdVertex4;

typedef struct RdScreen{
    vec2(size_t) size;
    vec3(float)* viewport;
    size_t _total;
    char* _buffer;
} RdScreen;

typedef struct RdVertexShader2{
    RdVertex3(*shader)(const RdVertex2*, struct RdVertexShader2*);
    std_small_vector(mat3f_ptr) matrices;
} RdVertexShader2;

typedef struct RdFragmentShader{
    float(*shader)(const vec2(int)* p, struct RdFragmentShader*);
    std_small_vector(float) attributes;
} RdFragmentShader;

typedef struct RdProgram2{
    RdVertexShader2* vshader;
    RdFragmentShader* fshader;
} RdProgram2;

typedef struct RdVertexShader3{
    RdVertex4(*shader)(const RdVertex3*, struct RdVertexShader3*);
    std_small_vector(mat3f_ptr) matrices;
} RdVertexShader3;

typedef struct RdProgram3{
    RdVertexShader3* vshader;
    RdFragmentShader* fshader;
} RdProgram3;

/////////////////////////////////////////////////////
//                 GLOBAL OBJECTS
/////////////////////////////////////////////////////


/*
    Grayscale representation in ascii took from:
    https://people.sc.fsu.edu/~jburkardt/data/ascii_art_grayscale/ascii_art_grayscale.html
    
    Also you can take a look at this resourse:
    http://mewbies.com/geek_fun_files/ascii/ascii_art_light_scale_and_gray_scale_chart.htm
*/
static char _rdColorBlackBack[] = " .'`^\",:;Il!i><~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";
static char _rdColorWhiteBack[] = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";


/////////////////////////////////////////////////////
//                      UTILS
/////////////////////////////////////////////////////
float rdAsciiToColor(char ascii){
    #ifndef RD_WHITE_BACK
    float _color = (float)(strchr(_rdColorBlackBack, ascii) - _rdColorBlackBack) / 69.0f;
    #else
    float _color = (float)(strchr(_rdColorWhiteBack, ascii) - _rdColorWhiteBack) / 69.0f;
    #endif

    return _color;
}

char _rdGetColor(float color){
    RD_NORMALIZED_FLOAT_MIN_ZERO(color)

    #ifndef RD_WHITE_BACK
    char _color = _rdColorBlackBack[(size_t)(color * 69)];
    #else
    char _color = _rdColorWhiteBack[(size_t)(color * 69)];
    #endif

    return _color;
}

void rdTranslate2(vec2(float) v, mat3(float)* m){
    m->m[0][0] = 1.0f;
    m->m[0][1] = 0.0f;
    m->m[0][2] = v.x;

    m->m[1][0] = 0.0f;
    m->m[1][1] = 1.0f;
    m->m[1][2] = v.y;

    m->m[2][0] = 0.0f;
    m->m[2][1] = 0.0f;
    m->m[2][2] = 1.0f;
}

void rdRotate2(float angle, mat3(float)* m){
    float rad = angle * 3.141592f / 180.0f;
    float s = sinf(rad);
    float c = cosf(rad);

    m->m[0][0] = c;
    m->m[0][1] = -s;
    m->m[0][2] = 0.0f;

    m->m[1][0] = s;
    m->m[1][1] = c;
    m->m[1][2] = 0.0f;

    m->m[2][0] = 0.0f;
    m->m[2][1] = 0.0f;
    m->m[2][2] = 1.0f;
}

void rdScale2(vec2(float) s, mat3(float)* m){
    m->m[0][0] = s.x;
    m->m[0][1] = 0.0f;
    m->m[0][2] = 0.0f;

    m->m[1][0] = 0.0f;
    m->m[1][1] = s.y;
    m->m[1][2] = 0.0f;

    m->m[2][0] = 0.0f;
    m->m[2][1] = 0.0f;
    m->m[2][2] = 1.0f;
}

/////////////////////////////////////////////////////
//                      SCREEN
/////////////////////////////////////////////////////
RdScreen rdCreateScreen(size_t w, size_t h){
    RdScreen result = {.size = {w, h},  ._total = w * h};
    result._buffer = malloc(result._total);
    result.viewport = NULL;

    return result;
}

void rdDestroyScreen(RdScreen* s){
    free(s->_buffer);
    s->size = (vec2(size_t)){0, 0};
    s->_total = 0;
    s->viewport = NULL;
    s->_buffer = NULL;
}

char* _rdGetBufferOffset(const vec2(int)* p, const RdScreen* s){
    if(p->x < 0 || p->y < 0) return NULL;
    if(p->x >= s->size.x || p->y >= s->size.y) return NULL;

    char* offset = s->_buffer + p->y * s->size.x + p->x;
    return offset;
}

vec2(int) _rdGetScreenPoint(vec3(float) v, const RdScreen* s){
    float c = s->viewport->z / v.z;
    v.x *= c;
    v.y *= c;

    int _x =  v.x * (s->size.x / s->viewport->x) / 2 + s->size.x / 2;
    int _y = s->size.y / 2 - v.y * (s->size.y / s->viewport->y) / 2;

    if(_x == s->size.x) _x--;
    if(_y == s->size.y) _y--;
    
    return (vec2(int)){_x, _y};
}

void _rdSetScreenPoint(const vec2(int)* p, float color, const RdScreen* s){
    char* offset = _rdGetBufferOffset(p, s);
    if(offset != 0) 
        *offset = _rdGetColor(color);
}

/////////////////////////////////////////////////////
//                     VIEWPORT
/////////////////////////////////////////////////////
vec3(float) rdCreateViewportIdentity(const RdScreen* s){
    float h = 2.0f * s->size.y;
    float w = s->size.x;

    if(w > h)
        return (vec3(float)){w / h, 1.0f, 1.0f};
    else
        return (vec3(float)){1.0f, h / w, 1.0f};
}

/////////////////////////////////////////////////////
//                      RENDER
/////////////////////////////////////////////////////
// base
void rdClear(RdScreen* s){
    #ifdef RD_SHOW_GRID
        #ifndef RD_WHITE_BACK
        memset(s->_buffer, '.', s->_total);
        #else
        memset(s->_buffer, '@', s->_total);
        #endif
    #else
        #ifndef RD_WHITE_BACK
        memset(s->_buffer, ' ', s->_total);
        #else
        memset(s->_buffer, '$', s->_total);
        #endif
    #endif
}

void rdFlush(){
    printf("\e[1;1H\e[2J");
}

void rdRender(const RdScreen* s){
    for(size_t i = 0; i < s->size.y; i++)
            printf("%.*s\n", s->size.x, s->_buffer + i * s->size.x);
}
void rdDRender(const RdScreen* s){
    printf("\e[?25l"); // disable cursor
    rdRender(s); // render
    printf("\e[%dA", s->size.y); // go up
    printf("\e[?25h"); // enable cursor
}

// single
void rdPoint2(const RdVertex2* v, RdProgram2* prog, const RdScreen* s){
    RdVertex3 new_v = prog->vshader->shader(v, prog->vshader);

    vec2(int) p = _rdGetScreenPoint(new_v.position, s);
    prog->fshader->attributes._data[0] = v->color;
    _rdSetScreenPoint(&p, prog->fshader->shader(&p, prog->fshader), s);
}

// multiple
void rdPoints2(const RdVertex2* verts, size_t count, RdProgram2* prog, const RdScreen* s){
    // #pragma omp parallel for schedule(guided)
    for(size_t i = 0; i < count; i++) rdPoint2(verts + i, prog, s);
}
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
// #define RD_SHOW_GRID
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

vec2(int) _rdMinScreenPoint(const vec2(int) p0, const vec2(int) p1, bool by_y){
    if(!by_y){
        if(p0.x < p1.x) return p0;
        return p1;
    }else{
        if(p0.y < p1.y) return p0;
        return p1;
    }
}
vec2(int) _rdMaxScreenPoint(const vec2(int) p0, const vec2(int) p1, bool by_y){
    if(!by_y){
        if(p0.x > p1.x) return p0;
        return p1;
    }else{
        if(p0.y > p1.y) return p0;
        return p1;
    }
}
vec2(int) _rdMidScreenPoint(const vec2(int) p0, const vec2(int) p1, const vec2(int) p2, bool by_y){
    if(!by_y){
        if((p0.x < p1.x && p0.x > p2.x) || (p0.x < p2.x && p0.x > p1.x)) return p0;
        else if((p1.x < p2.x && p1.x > p0.x) || (p1.x < p0.x && p1.x > p2.x)) return p1;
        return p2;
    }else{
        if((p0.y < p1.y && p0.y > p2.y) || (p0.y < p2.y && p0.y > p1.y)) return p0;
        else if((p1.y < p2.y && p1.y > p0.y) || (p1.y < p0.y && p1.y > p2.y)) return p1;
        return p2;
    }
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

// hidden
void _rdLine(vec2(int) p0, vec2(int) p1, vec2(float) colors, RdFragmentShader* frag, RdScreen* s){
    int dx = p1.x - p0.x;
    int dy = p1.y - p0.y;
    size_t max = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float step_x = (float)dx / max;
    float step_y = (float)dy / max;

    vec2(float) colors_x = {0, max};
    vec2(float) colors_f = lininter(float)(colors_x, colors);

    #pragma omp parallel for schedule(guided)
    for(size_t i = 0; i <= max; i++){
        vec2(int) p = {p0.x + i * step_x, p0.y + i * step_y};

        float color = vec2_mul_vec2(float)((vec2(float)){i, 1}, colors_f);
        frag->attributes._data[0] = color;
        _rdSetScreenPoint(&p, frag->shader(&p, frag), s);
    }
}
void _rdTriangle(vec2(int) p0, vec2(int) p1, vec2(int) p2, vec3(float) colors, RdFragmentShader* frag, RdScreen* s){
    vec2(int) min = _rdMinScreenPoint(_rdMinScreenPoint(p0, p1, false), p2, false);
    vec2(int) mid = _rdMidScreenPoint(p0, p1, p2, false);
    vec2(int) max = _rdMaxScreenPoint(_rdMaxScreenPoint(p0, p1, false), p2, false);

    int dx0 = mid.x - min.x;
    int dy0 = mid.y - min.y;
    float s0 = (float)dy0 / dx0;

    int dx1 = max.x - min.x;
    int dy1 = max.y - min.y;
    float s1 = (float)dy1 / dx1;

    int dx2 = max.x - mid.x;
    int dy2 = max.y - mid.y;
    float s2 = (float)dy2 / dx2;

    vec3(float) colors_x = (vec3(float)){p0.x, p1.x, p2.x};
    vec3(float) colors_y = (vec3(float)){p0.y, p1.y, p2.y};
    vec3(float) colors_f = lininter2(float)(colors_x, colors_y, colors);

    // first triangle
    for(int x = min.x; x <= mid.x; x++){
        int to = s0 > 0 ? s0 * (x - min.x) + min.y : s1 * (x - min.x) + min.y;
        int from = s0 < 0 ? s0 * (x - min.x) + min.y : s1 * (x - min.x) + min.y;
        
        for(int y = from; y <= to; y++){
            float color = vec3_mul_vec3(float)((vec3(float)){x, y, 1}, colors_f);
            frag->attributes._data[0] = color;
            vec2(int) p = {x, y};
            _rdSetScreenPoint(&p, frag->shader(&p, frag), s);
        }
    }

    // second triangle
    for(int x = mid.x; x <= max.x; x++){
        int to = s2 > 0 ? s1 * (x - min.x) + min.y : s2 * (x - mid.x) + mid.y;
        int from = s2 < 0 ? s1 * (x - min.x) + min.y : s2 * (x - mid.x) + mid.y;
        
        for(int y = from; y <= to; y++){
            float color = vec3_mul_vec3(float)((vec3(float)){x, y, 1}, colors_f);
            frag->attributes._data[0] = color;
            vec2(int) p = {x, y};
            _rdSetScreenPoint(&p, frag->shader(&p, frag), s);
        } 
    }
}

// single
void rdPoint2(const RdVertex2* v, RdProgram2* prog, const RdScreen* s){
    RdVertex3 new_v = prog->vshader->shader(v, prog->vshader);

    vec2(int) p = _rdGetScreenPoint(new_v.position, s);
    prog->fshader->attributes._data[0] = v->color;
    _rdSetScreenPoint(&p, prog->fshader->shader(&p, prog->fshader), s);
}
void rdLine2(const RdVertex2* v0, const RdVertex2* v1, RdProgram2* prog, RdScreen* s){
    RdVertex3 new_v0 = prog->vshader->shader(v0, prog->vshader);
    RdVertex3 new_v1 = prog->vshader->shader(v1, prog->vshader);

    vec2(int) p0 = _rdGetScreenPoint(new_v0.position, s);
    vec2(int) p1 = _rdGetScreenPoint(new_v1.position, s);
   
    _rdLine(p0, p1, (vec2(float)){new_v0.color, new_v1.color}, prog->fshader, s);
}
void rdTriangle2(const RdVertex2* v0, const RdVertex2* v1, const RdVertex2* v2, RdProgram2* prog, RdScreen* s){
    RdVertex3 new_v0 = prog->vshader->shader(v0, prog->vshader);
    RdVertex3 new_v1 = prog->vshader->shader(v1, prog->vshader);
    RdVertex3 new_v2 = prog->vshader->shader(v2, prog->vshader);

    vec2(int) p0 = _rdGetScreenPoint(new_v0.position, s);
    vec2(int) p1 = _rdGetScreenPoint(new_v1.position, s);
    vec2(int) p2 = _rdGetScreenPoint(new_v2.position, s);

    _rdTriangle(p0, p1, p2, (vec3(float)){new_v0.color, new_v1.color, new_v2.color}, prog->fshader, s);
}

// multiple
void rdPoints2(const RdVertex2* verts, size_t count, RdProgram2* prog, const RdScreen* s){
    // #pragma omp parallel for schedule(guided)
    for(size_t i = 0; i < count; i++) rdPoint2(verts + i, prog, s);
}

void rdLines2(const RdVertex2* verts, vec2(size_t)* indexes, size_t indexes_count, RdProgram2* prog, RdScreen* s){
    // #pragma omp parallel for schedule(guided)
    for(size_t i = 0; i < indexes_count; i++)
        rdLine2(verts + indexes[i].x, verts + indexes[i].y, prog, s);
}
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
//         VECTOR ON STACK (small_vector.h)
/////////////////////////////////////////////////////
#ifndef STD_SMALL_VECTOR_MAX_SIZE
#define STD_SMALL_VECTOR_MAX_SIZE 256
#endif

#ifndef auto
#define auto __auto_type
#endif

#ifndef __cat
#define __cat(X, Y) X##Y
#endif

#ifndef _cat
#define _cat(X, Y) __cat(X, Y)
#endif

// definitions
#define std_small_vector(T) _cat(_std_small_vector_, T)

#define SMALL_VECTORS(T) typedef struct std_small_vector(T){\
    size_t _size;\
    T _data[STD_SMALL_VECTOR_MAX_SIZE];\
    void (*clear)(struct std_small_vector(T)*);\
    size_t (*size)(struct std_small_vector(T)*);\
    const T* (*data)(struct std_small_vector(T)*);\
    T* (*at)(struct std_small_vector(T)*, size_t);\
    T* (*begin)(struct std_small_vector(T)*);\
    T* (*end)(struct std_small_vector(T)*);\
    T* (*back)(struct std_small_vector(T)*);\
    void (*push_back)(struct std_small_vector(T)*, T);\
    T (*pop_back)(struct std_small_vector(T)*);\
} std_small_vector(T);\
typedef T* _cat(_iter, std_small_vector(T));\
void _cat(_clear, std_small_vector(T))(std_small_vector(T)* svec){\
    svec->_size = 0;\
}\
size_t _cat(_size, std_small_vector(T))(std_small_vector(T)* svec){\
    return svec->_size;\
}\
const T* _cat(_data, std_small_vector(T))(std_small_vector(T)* svec){\
    return svec->_data;\
}\
T* _cat(_at, std_small_vector(T))(std_small_vector(T)* svec, size_t index){\
    if(index >= svec->_size){\
        fprintf(stderr, "std::small_vector [at]: index %d is out of bounds\n", index);\
        exit(EXIT_FAILURE);\
    }\
    return &svec->_data[index];\
}\
T* _cat(_begin, std_small_vector(T))(std_small_vector(T)* svec){\
    return svec->_data;\
}\
T* _cat(_end, std_small_vector(T))(std_small_vector(T)* svec){\
    return svec->_data + svec->_size;\
}\
T* _cat(_back, std_small_vector(T))(std_small_vector(T)* svec){\
    return svec->_data + svec->_size - 1;\
}\
void _cat(_push_back, std_small_vector(T))(std_small_vector(T)* svec, T value){\
    svec->_size++;\
    if(svec->_size > STD_SMALL_VECTOR_MAX_SIZE){\
        fprintf(stderr, "std::small_vector [push_back]: out of reserve\n");\
        exit(EXIT_FAILURE);\
    }\
    *svec->back(svec) = value;\
}\
T _cat(_pop_back, std_small_vector(T))(std_small_vector(T)* svec){\
    T result = *svec->back(svec);\
    svec->_size--;\
    return result;\
}

// methods
#define std_small_vector_iterator(T) _cat(_iter, std_small_vector(T))

#ifndef std_begin
#define std_begin(CONTAINER) (CONTAINER).begin(&(CONTAINER))
#endif

#ifndef std_end
#define std_end(CONTAINER) (CONTAINER).end(&(CONTAINER))
#endif

#ifndef std_back
#define std_back(CONTAINER) (CONTAINER).back(&(CONTAINER))
#endif

#ifndef std_swap
#define std_swap(ITER1, ITER2) *(ITER1) ^= *(ITER2) ^= *(ITER1) ^= *(ITER2)
#endif

#ifndef foreach
#define foreach(CONTAINER) for(__typeof__(std_begin(CONTAINER)) it = std_begin(CONTAINER);\
it < std_end(CONTAINER);\
it++)
#endif


#define std_small_vector_default(T) (std_small_vector(T)){\
    ._size = 0, \
    .clear = _cat(_clear, std_small_vector(T)), \
    .size = _cat(_size, std_small_vector(T)), \
    .data = _cat(_data, std_small_vector(T)), \
    .at = _cat(_at, std_small_vector(T)), \
    .begin = _cat(_begin, std_small_vector(T)), \
    .end = _cat(_end, std_small_vector(T)), \
    .back = _cat(_back, std_small_vector(T)), \
    .push_back = _cat(_push_back, std_small_vector(T)), \
    .pop_back = _cat(_pop_back, std_small_vector(T))\
}

// types

/////////////////////////////////////////////////////
//                 LINEAR ALGREBRA (linear.h)
/////////////////////////////////////////////////////
#ifndef auto
#define auto __auto_type
#endif

#ifndef __cat
#define __cat(X, Y) X##Y
#endif

#ifndef _cat
#define _cat(X, Y) __cat(X, Y)
#endif

// definitions
#define vec2(T) _cat(_vec2_, T)
#define vec3(T) _cat(_vec3_, T)
#define vec4(T) _cat(_vec4_, T)
#define mat2(T) _cat(_mat2_, T)
#define mat3(T) _cat(_mat3_, T)
#define mat4(T) _cat(_mat4_, T)

#define LINEAR(T) \
typedef struct vec2(T){\
    T x, y;\
} vec2(T);\
typedef struct vec3(T){\
    T x, y, z;\
} vec3(T);\
typedef struct vec4(T){\
    T x, y, z, w;\
} vec4(T);\
typedef struct mat2(T){\
    T m[2][2];\
} mat2(T);\
typedef struct mat3(T){\
    T m[3][3];\
} mat3(T);\
typedef struct mat4(T){\
    T m[4][4];\
} mat4(T);\
T _cat(vec2(T), vec2(T))(const vec2(T)* v0, const vec2(T)* v1){\
    return v0->x * v1->x + v0->y * v1->y;\
}\
vec2(T) _cat(vec2(T), mat2(T))(const vec2(T)* v, const mat2(T)* m){\
    vec2(T) result;\
    result.x = v->x * m->m[0][0] + v->y * m->m[1][0];\
    result.y = v->x * m->m[0][1] + v->y * m->m[1][1];\
    return result;\
}\
vec2(T) _cat(mat2(T), vec2(T))(const vec2(T)* v, const mat2(T)* m){\
    vec2(T) result;\
    result.x = m->m[0][0] * v->x + m->m[0][1]* v->y;\
    result.y = m->m[1][0] * v->x + m->m[1][1] * v->y;\
    return result;\
}\
mat2(T) _cat(mat2(T), mat2(T))(const mat2(T)* m0, const mat2(T)* m1){\
    mat2(T) result;\
    result.m[0][0] = m0->m[0][0] * m1->m[0][0] + m0->m[0][1] * m1->m[1][0];\
    result.m[0][1] = m0->m[0][0] * m1->m[0][1] + m0->m[0][1] * m1->m[1][1];\
    result.m[1][0] = m0->m[1][0] * m1->m[0][0] + m0->m[1][1] * m1->m[1][0];\
    result.m[1][1] = m0->m[1][0] * m1->m[0][1] + m0->m[1][1] * m1->m[1][1];\
    return result;\
}\
T _cat(vec3(T), vec3(T))(const vec3(T)* v0, const vec3(T)* v1){\
    return v0->x * v1->x + v0->y * v1->y + v0->z * v1->z;\
}\
vec3(T) _cat(vec3(T), mat3(T))(const vec3(T)* v, const mat3(T)* m){\
    vec3(T) result;\
    result.x = v->x * m->m[0][0] + v->y * m->m[1][0] + v->z * m->m[2][0];\
    result.y = v->x * m->m[0][1] + v->y * m->m[1][1] + v->z * m->m[2][1];\
    result.z = v->x * m->m[0][2] + v->y * m->m[1][2] + v->z * m->m[2][2];\
    return result;\
}\
vec3(T) _cat(mat3(T), vec3(T))(const vec3(T)* v, const mat3(T)* m){\
    vec3(T) result;\
    result.x = m->m[0][0] * v->x + m->m[0][1] * v->y + m->m[0][2] * v->z;\
    result.y = m->m[1][0] * v->x + m->m[1][1] * v->y + m->m[1][2] * v->z;\
    result.z = m->m[2][0] * v->x + m->m[2][1] * v->y + m->m[2][2] * v->z;\
    return result;\
}\
mat3(T) _cat(mat3(T), mat3(T))(const mat3(T)* m0, const mat3(T)* m1){\
    mat3(T) result;\
    result.m[0][0] = m0->m[0][0] * m1->m[0][0] + m0->m[0][1] * m1->m[1][0] + m0->m[0][2] * m1->m[2][0];\
    result.m[0][1] = m0->m[0][0] * m1->m[0][1] + m0->m[0][1] * m1->m[1][1] + m0->m[0][2] * m1->m[2][1];\
    result.m[0][2] = m0->m[0][0] * m1->m[0][2] + m0->m[0][1] * m1->m[1][2] + m0->m[0][2] * m1->m[2][2];\
    result.m[1][0] = m0->m[1][0] * m1->m[0][0] + m0->m[1][1] * m1->m[1][0] + m0->m[1][2] * m1->m[2][0];\
    result.m[1][1] = m0->m[1][0] * m1->m[0][1] + m0->m[1][1] * m1->m[1][1] + m0->m[1][2] * m1->m[2][1];\
    result.m[1][2] = m0->m[1][0] * m1->m[0][2] + m0->m[1][1] * m1->m[1][2] + m0->m[1][2] * m1->m[2][2];\
    result.m[2][0] = m0->m[2][0] * m1->m[0][0] + m0->m[2][1] * m1->m[1][0] + m0->m[2][2] * m1->m[2][0];\
    result.m[2][1] = m0->m[2][0] * m1->m[0][1] + m0->m[2][1] * m1->m[1][1] + m0->m[2][2] * m1->m[2][1];\
    result.m[2][2] = m0->m[2][0] * m1->m[0][2] + m0->m[2][1] * m1->m[1][2] + m0->m[2][2] * m1->m[2][2];\
    return result;\
}\
T _cat(vec3(T), vec2(T))(const vec3(T)* v0, const vec2(T)* v1){\
    vec3(T) temp = {v1->x, v1->y, 1};\
    return vec3vec3(T)(v0, &temp);\
}\
vec3(T) _cat(vec2(T), mat3(T))(const vec2(T)* v, const mat3(T)* m){\
    vec3(T) temp = {v->x, v->y, 1};\
    return vec3mat3(T)(&temp, m);\
}\
vec3(T) _cat(mat3(T), vec2(T))(const vec2(T)* v, const mat3(T)* m){\
    vec3(T) temp = {v->x, v->y, 1};\
    return mat3vec3(T)(&temp, m);\
}\
T _cat(vec4(T), vec4(T))(const vec4(T)* v0, const vec4(T)* v1){\
    return v0->x * v1->x + v0->y * v1->y + v0->z * v1->z + v0->w * v1->w;\
}\
vec4(T) _cat(vec4(T), mat4(T))(const vec4(T)* v, const mat4(T)* m){\
    vec4(T) result;\
    result.x = v->x * m->m[0][0] + v->y * m->m[1][0] + v->z * m->m[2][0] + v->w * m->m[3][0];\
    result.y = v->x * m->m[0][1] + v->y * m->m[1][1] + v->z * m->m[2][1] + v->w * m->m[3][1];\
    result.z = v->x * m->m[0][2] + v->y * m->m[1][2] + v->z * m->m[2][2] + v->w * m->m[3][2];\
    result.w = v->x * m->m[0][3] + v->y * m->m[1][3] + v->z * m->m[2][3] + v->w * m->m[3][3];\
    return result;\
}\
vec4(T) _cat(mat4(T), vec4(T))(const vec4(T)* v, const mat4(T)* m){\
    vec4(T) result;\
    result.x = m->m[0][0] * v->x + m->m[0][1] * v->y + m->m[0][2] * v->z + m->m[0][3] * v->w;\
    result.y = m->m[1][0] * v->x + m->m[1][1] * v->y + m->m[1][2] * v->z + m->m[1][3] * v->w;\
    result.z = m->m[2][0] * v->x + m->m[2][1] * v->y + m->m[2][2] * v->z + m->m[2][3] * v->w;\
    result.w = m->m[3][0] * v->x + m->m[3][1] * v->y + m->m[3][2] * v->z + m->m[3][3] * v->w;\
    return result;\
}\
mat4(T) _cat(mat4(T), mat4(T))(const mat4(T)* m0, const mat4(T)* m1){\
    mat4(T) result;\
    result.m[0][0] = m0->m[0][0] * m1->m[0][0] + m0->m[0][1] * m1->m[1][0] + m0->m[0][2] * m1->m[2][0] + m0->m[0][3] * m1->m[3][0];\
    result.m[0][1] = m0->m[0][0] * m1->m[0][1] + m0->m[0][1] * m1->m[1][1] + m0->m[0][2] * m1->m[2][1] + m0->m[0][3] * m1->m[3][1];\
    result.m[0][2] = m0->m[0][0] * m1->m[0][2] + m0->m[0][1] * m1->m[1][2] + m0->m[0][2] * m1->m[2][2] + m0->m[0][3] * m1->m[3][2];\
    result.m[0][3] = m0->m[0][0] * m1->m[0][3] + m0->m[0][1] * m1->m[1][3] + m0->m[0][2] * m1->m[2][3] + m0->m[0][3] * m1->m[3][3];\
    result.m[1][0] = m0->m[1][0] * m1->m[0][0] + m0->m[1][1] * m1->m[1][0] + m0->m[1][2] * m1->m[2][0] + m0->m[1][3] * m1->m[3][0];\
    result.m[1][1] = m0->m[1][0] * m1->m[0][1] + m0->m[1][1] * m1->m[1][1] + m0->m[1][2] * m1->m[2][1] + m0->m[1][3] * m1->m[3][1];\
    result.m[1][2] = m0->m[1][0] * m1->m[0][2] + m0->m[1][1] * m1->m[1][2] + m0->m[1][2] * m1->m[2][2] + m0->m[1][3] * m1->m[3][2];\
    result.m[1][3] = m0->m[1][0] * m1->m[0][3] + m0->m[1][1] * m1->m[1][3] + m0->m[1][2] * m1->m[2][3] + m0->m[1][3] * m1->m[3][3];\
    result.m[2][0] = m0->m[2][0] * m1->m[0][0] + m0->m[2][1] * m1->m[1][0] + m0->m[2][2] * m1->m[2][0] + m0->m[2][3] * m1->m[3][0];\
    result.m[2][1] = m0->m[2][0] * m1->m[0][1] + m0->m[2][1] * m1->m[1][1] + m0->m[2][2] * m1->m[2][1] + m0->m[2][3] * m1->m[3][1];\
    result.m[2][2] = m0->m[2][0] * m1->m[0][2] + m0->m[2][1] * m1->m[1][2] + m0->m[2][2] * m1->m[2][2] + m0->m[2][3] * m1->m[3][2];\
    result.m[2][3] = m0->m[2][0] * m1->m[0][3] + m0->m[2][1] * m1->m[1][3] + m0->m[2][2] * m1->m[2][3] + m0->m[2][3] * m1->m[3][3];\
    result.m[3][0] = m0->m[3][0] * m1->m[0][0] + m0->m[3][1] * m1->m[1][0] + m0->m[3][2] * m1->m[2][0] + m0->m[3][3] * m1->m[3][0];\
    result.m[3][1] = m0->m[3][0] * m1->m[0][1] + m0->m[3][1] * m1->m[1][1] + m0->m[3][2] * m1->m[2][1] + m0->m[3][3] * m1->m[3][1];\
    result.m[3][2] = m0->m[3][0] * m1->m[0][2] + m0->m[3][1] * m1->m[1][2] + m0->m[3][2] * m1->m[2][2] + m0->m[3][3] * m1->m[3][2];\
    result.m[3][3] = m0->m[3][0] * m1->m[0][3] + m0->m[3][1] * m1->m[1][3] + m0->m[3][2] * m1->m[2][3] + m0->m[3][3] * m1->m[3][3];\
    return result;\
}\
T _cat(vec4(T), vec3(T))(const vec4(T)* v0, const vec3(T)* v1){\
    vec4(T) temp = {v1->x, v1->y, v1->z, 1};\
    return vec4vec4(T)(v0, &temp);\
}\
vec4(T) _cat(vec3(T), mat4(T))(const vec3(T)* v, const mat4(T)* m){\
    vec4(T) temp = {v->x, v->y, v->z, 1};\
    return vec4mat4(T)(&temp, m);\
}\
vec4(T) _cat(mat4(T), vec3(T))(const vec3(T)* v, const mat4(T)* m){\
    vec4(T) temp = {v->x, v->y, v->z, 1};\
    return mat4vec4(T)(&temp, m);\
}


// methods
#define vec2vec2(T) _cat(vec2(T), vec2(T))
#define vec2mat2(T) _cat(vec2(T), mat2(T))
#define mat2vec2(T) _cat(mat2(T), vec2(T))
#define mat2mat2(T) _cat(mat2(T), mat2(T))

#define vec3vec3(T) _cat(vec3(T), vec3(T))
#define vec3mat3(T) _cat(vec3(T), mat3(T))
#define mat3vec3(T) _cat(mat3(T), vec3(T))
#define mat3mat3(T) _cat(mat3(T), mat3(T))

#define vec3vec2(T) _cat(vec3(T), vec2(T))
#define vec2vec3(T) _cat(vec3(T), vec2(T))
#define vec2mat3(T) _cat(vec2(T), mat3(T))
#define mat3vec2(T) _cat(mat3(T), vec2(T))

#define vec4vec4(T) _cat(vec4(T), vec4(T))
#define vec4mat4(T) _cat(vec4(T), mat4(T))
#define mat4vec4(T) _cat(mat4(T), vec4(T))
#define mat4mat4(T) _cat(mat4(T), mat4(T))

#define vec4vec3(T) _cat(vec4(T), vec3(T))
#define vec3vec4(T) _cat(vec4(T), vec3(T))
#define vec3mat4(T) _cat(vec3(T), mat4(T))
#define mat4vec3(T) _cat(mat4(T), vec3(T))

// types
LINEAR(float)
LINEAR(double)
LINEAR(size_t)
LINEAR(int)


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
    size_t _total;
    vec3(float)* viewport;
    char* _buffer;
} RdScreen;


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

/////////////////////////////////////////////////////
//                     VIEWPORT
/////////////////////////////////////////////////////
vec3(float) rdCreateViewportIdentity(RdScreen* s){
    float h = 2.0f * s->size.y;
    float w = s->size.x;

    if(w > h)
        return (vec3(float)){1.0f, w / h, 1.0f};
    else
        return (vec3(float)){h / w, 1.0f, 1.0f};
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

void rdRender(RdScreen* s){
    for(size_t i = 0; i < s->size.y; i++)
            printf("%.*s\n", s->size.x, s->_buffer + i * s->size.x);
}
void rdDRender(RdScreen* s){
    printf("\e[?25l"); // disable cursor
    rdRender(s); // render
    printf("\e[%dA", s->size.y); // go up
    printf("\e[?25h"); // enable cursor
}
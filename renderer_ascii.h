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
//                     MACROS
/////////////////////////////////////////////////////
#define RD_NORMALIZED_FLOAT(X) if(X < -1.0f) X = -1.0f;\
else if(X > 1.0f) X = 1.0f;

#define RD_NORMALIZED_FLOAT_MIN_ZERO(X) if(X < 0.0f) X = 0.0f;\
else if(X > 1.0f) X = 1.0f;

// #define RD_DEBUG
#define RD_SHOW_GRID
// #define RD_WHITE_BACK

/////////////////////////////////////////////////////
//                 DATA STRUCTURES
/////////////////////////////////////////////////////
typedef enum {LINES, LINE_STRIP, LINE_LOOP, LINES_FULL} RD_LINES;

typedef struct RdVertex2f{
    float x, y, color;
} RdVertex2f;

typedef struct RdVertex3f{
    float x, y, z, color;
} RdVertex3f;

typedef struct RdViewport{
    float h, w, d;
} RdViewport;

typedef struct RdScreen{
    size_t h, w, total;
    RdViewport* viewport;    
    char* buffer;
} RdScreen;

typedef struct RdScreenPoint{
    size_t x, y;
} RdScreenPoint;


/////////////////////////////////////////////////////
//                   GLOBAL OBJECTS
/////////////////////////////////////////////////////

float rdTranslate3f[4][4] = {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
};
float rdRotate3f[4][4] = {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
};
float rdScale3f[4][4] = {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
};

float rdTranslate2f[3][3] = {
    {1, 0, 0},
    {0, 1, 0},
    {0, 0, 1}
};
float rdRotate2f[3][3] = {
    {1, 0, 0},
    {0, 1, 0},
    {0, 0, 1}
};
float rdScale2f[3][3] = {
    {1, 0, 0},
    {0, 1, 0},
    {0, 0, 1}
};


/*
    - grayscale representation in ascii took from:
    https://people.sc.fsu.edu/~jburkardt/data/ascii_art_grayscale/ascii_art_grayscale.html
    
    - also you can take a look at this resourse:
    http://mewbies.com/geek_fun_files/ascii/ascii_art_light_scale_and_gray_scale_chart.htm
*/
static char _rdColorBlackBack[] = " .'`^\",:;Il!i><~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";
static char _rdColorWhiteBack[] = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";


/////////////////////////////////////////////////////
//                      UTILS
/////////////////////////////////////////////////////
float rdAsciiToColorf(char ascii){
    #ifndef RD_WHITE_BACK
    float _color = (float)(strchr(_rdColorBlackBack, ascii) - _rdColorBlackBack) / 69.0f;
    #else
    float _color = (float)(strchr(_rdColorWhiteBack, ascii) - _rdColorWhiteBack) / 69.0f;
    #endif

    return _color;
}

char _rdGetColorf(float color){
    RD_NORMALIZED_FLOAT_MIN_ZERO(color)

    #ifndef RD_WHITE_BACK
    char _color = _rdColorBlackBack[(size_t)(color * 69)];
    #else
    char _color = _rdColorWhiteBack[(size_t)(color * 69)];
    #endif

    return _color;
}

float maxf(float x, float y){
    return x > y ? x : y;
}

// 2D
void rdSetTranslate2f(float x, float y){
    rdTranslate2f[0][0] = 1.0f;
    rdTranslate2f[0][1] = 0.0f;
    rdTranslate2f[0][2] = x;

    rdTranslate2f[1][0] = 0.0f;
    rdTranslate2f[1][1] = 1.0f;
    rdTranslate2f[1][2] = y;

    rdTranslate2f[2][0] = 0.0f;
    rdTranslate2f[2][1] = 0.0f;
    rdTranslate2f[2][2] = 1.0f;
}

void rdSetRotate2f(float angle){
    float rad = angle * 3.1416f / 180.0f;
    float s = sinf(rad);
    float c = cosf(rad);

    rdRotate2f[0][0] = c;
    rdRotate2f[0][1] = -s;
    rdRotate2f[0][2] = 0.0f;

    rdRotate2f[1][0] = s;
    rdRotate2f[1][1] = c;
    rdRotate2f[1][2] = 0.0f;

    rdRotate2f[2][0] = 0.0f;
    rdRotate2f[2][1] = 0.0f;
    rdRotate2f[2][2] = 1.0f;
}

void rdSetScale2f(float sx, float sy){
    rdScale2f[0][0] = sx;
    rdScale2f[0][1] = 0.0f;
    rdScale2f[0][2] = 0.0f;

    rdScale2f[1][0] = 0.0f;
    rdScale2f[1][1] = sy;
    rdScale2f[1][2] = 0.0f;

    rdScale2f[2][0] = 0.0f;
    rdScale2f[2][1] = 0.0f;
    rdScale2f[2][2] = 1.0f;
}

RdVertex2f rdMat3Mul2f(RdVertex2f* v, float mat[3][3]){
    float x, y, w;

    x = v->x * mat[0][0] + v->y * mat[0][1] + mat[0][2];
    y = v->x * mat[1][0] + v->y * mat[1][1] + mat[1][2];
    w = v->x * mat[2][0] + v->y * mat[2][1] + mat[2][2];

    return (RdVertex2f){x, y, v->color};
}

// 3D
void rdSetTranslate3f(float x, float y, float z){
    rdTranslate3f[0][0] = 1.0f;
    rdTranslate3f[0][1] = 0.0f;
    rdTranslate3f[0][2] = 0.0f;
    rdTranslate3f[0][3] = x;

    rdTranslate3f[1][0] = 0.0f;
    rdTranslate3f[1][1] = 1.0f;
    rdTranslate3f[1][2] = 0.0f;
    rdTranslate3f[1][3] = y;

    rdTranslate3f[2][0] = 0.0f;
    rdTranslate3f[2][1] = 0.0f;
    rdTranslate3f[2][2] = 1.0f;
    rdTranslate3f[2][3] = z;

    rdTranslate3f[3][0] = 0.0f;
    rdTranslate3f[3][1] = 0.0f;
    rdTranslate3f[3][2] = 0.0f;
    rdTranslate3f[3][3] = 1.0f;
}
void rdSetRotate3f(float x, float y, float z, float angle){
    float mod = sqrtf(x * x + y * y + z * z);
    x /= mod;
    y /= mod;
    z /= mod;

    float rad = angle * 3.1416f / 180.0f;
    float s = sinf(rad);
    float c = cosf(rad);

    float sx = x * s;
    float sy = y * s;
    float sz = z * s;

    float ic = 1.0f - c;
    float icx = ic * x;
    float icy = ic * y;

    rdRotate3f[0][0] = c + icx * x;
    rdRotate3f[0][1] = icx * y - sz;
    rdRotate3f[0][2] = icx * z + sy;
    rdRotate3f[0][3] = 0.0f;

    rdRotate3f[1][0] = icx * y + sz;
    rdRotate3f[1][1] = c + icy * y;
    rdRotate3f[1][2] = icy * z - sx;
    rdRotate3f[1][3] = 0.0f;

    rdRotate3f[2][0] = icx * z - sy;
    rdRotate3f[2][1] = icy * z + sx;
    rdRotate3f[2][2] = c + ic * z * z;
    rdRotate3f[2][3] = 0.0f;

    rdRotate3f[3][0] = 0.0f;
    rdRotate3f[3][1] = 0.0f;
    rdRotate3f[3][2] = 0.0f;
    rdRotate3f[3][3] = 1.0f;
}

void rdSetScale3f(float sx, float sy, float sz){
    rdScale3f[0][0] = sx;
    rdScale3f[0][1] = 0.0f;
    rdScale3f[0][2] = 0.0f;
    rdScale3f[0][3] = 0.0f;

    rdScale3f[1][0] = 0.0f;
    rdScale3f[1][1] = sy;
    rdScale3f[1][2] = 0.0f;
    rdScale3f[1][3] = 0.0f;

    rdScale3f[2][0] = 0.0f;
    rdScale3f[2][1] = 0.0f;
    rdScale3f[2][2] = sz;
    rdScale3f[2][3] = 0.0f;

    rdScale3f[3][0] = 0.0f;
    rdScale3f[3][1] = 0.0f;
    rdScale3f[3][2] = 0.0f;
    rdScale3f[3][3] = 1.0f;
}

RdVertex3f rdMat4Mul3f(RdVertex3f* v, float mat[4][4]){
    float x, y, z, w;

    x = v->x * mat[0][0] + v->y * mat[0][1] + v->z * mat[0][2] + mat[0][3];
    y = v->x * mat[1][0] + v->y * mat[1][1] + v->z * mat[1][2] + mat[1][3];
    z = v->x * mat[2][0] + v->y * mat[2][1] + v->z * mat[2][2] + mat[2][3];
    w = v->x * mat[3][0] + v->y * mat[3][1] + v->z * mat[3][2] + mat[3][3];

    return (RdVertex3f){x, y, z, v->color};
}


/////////////////////////////////////////////////////
//                      SCREEN
/////////////////////////////////////////////////////
RdScreen rdCreateScreen(size_t w, size_t h){
    RdScreen result = {.h = h, .w = w, .total = h * w};
    result.buffer = malloc(h * w);
    result.viewport = NULL;

    return result;
}

RdViewport rdCreateViewportIdentity(RdScreen* screen){
    float identity = (float)screen->w / screen->h;
    RdViewport result = {1.0f, identity / 2.0f, 1.0f};
    return result;
}

void rdDestroyScreen(RdScreen* screen){
    free(screen->buffer);
}

char* _rdGetBufferOffset(RdScreenPoint* p, RdScreen* screen){
    if(p->x >= screen->w || p->y >= screen->h) return NULL;

    char* offset = screen->buffer + p->y * screen->w + p->x;
    return offset;
}

RdScreenPoint _rdGetScreenPoint2f(float x, float y, RdScreen* screen){
    size_t _x =  x * (screen->w / screen->viewport->w) / 2 + screen->w / 2;
    size_t _y = screen->h / 2 - y * (screen->h / screen->viewport->h) / 2;

    if(_x == screen->w) _x--;
    if(_y == screen->h) _y--;
    
    return (RdScreenPoint){_x, _y};
}
RdScreenPoint _rdGetScreenPoint3f(float x, float y, float z, RdScreen* screen){
    float c = screen->viewport->d / z;
    x *= c;
    y *= c;

    size_t _x =  x * (screen->w / screen->viewport->w) / 2 + screen->w / 2;
    size_t _y = screen->h / 2 - y * (screen->h / screen->viewport->h) / 2;

    if(_x == screen->w) _x--;
    if(_y == screen->h) _y--;
    
    return (RdScreenPoint){_x, _y};
}

void _rdSetScreenPoint(RdScreenPoint* p, float color, RdScreen* screen){
    char* offset = _rdGetBufferOffset(p, screen);
    if(offset != 0) 
        *offset = _rdGetColorf(color);
}


/////////////////////////////////////////////////////
//                      RENDER
/////////////////////////////////////////////////////
// base
void rdClear(RdScreen* screen){
    #ifdef RD_SHOW_GRID
        #ifndef RD_WHITE_BACK
        memset(screen->buffer, '.', screen->total);
        #else
        memset(screen->buffer, '@', screen->total);
        #endif
    #else
        #ifndef RD_WHITE_BACK
        memset(screen->buffer, ' ', screen->total);
        #else
        memset(screen->buffer, '$', screen->total);
        #endif
    #endif
}

void rdFlush(){
    printf("\e[1;1H\e[2J");
}

void rdRender(RdScreen* screen){
    for(size_t i = 0; i < screen->h; i++)
            printf("%.*s\n", screen->w, screen->buffer + i * screen->w);
}
void rdDRender(RdScreen* screen){
    printf("\e[?25l"); // disable cursor
    for(size_t i = 0; i < screen->h; i++)
            printf("%.*s\n", screen->w, screen->buffer + i * screen->w);
    printf("\e[%dA", screen->h); // go up
    printf("\e[?25h"); // enable cursor
}

// hidden
void _rdLine(RdScreenPoint* p0, RdScreenPoint* p1, float color0, float color1, RdScreen* screen){
    int dx = (int)p1->x - (int)p0->x;
    int dy = (int)p0->y - (int)p1->y;
    size_t max = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float step_x = (float)dx / max;
    float step_y = (float)dy / max;

    float step_color = (color1 - color0) / max;

    #pragma omp parallel for schedule(guided)
    for(size_t i = 0; i <= max; i++){
        RdScreenPoint p = {p0->x + i * step_x, p0->y - i * step_y};
        _rdSetScreenPoint(&p, color0 + i * step_color, screen);
    }
}

// single
void rdPoint2f(RdVertex2f* v,  RdScreen* screen){
    RdVertex2f new_v = rdMat3Mul2f(v, rdScale2f);
    new_v = rdMat3Mul2f(&new_v, rdRotate2f);
    new_v = rdMat3Mul2f(&new_v, rdTranslate2f);

    RdScreenPoint p = _rdGetScreenPoint2f(new_v.x, new_v.y, screen);
    _rdSetScreenPoint(&p, new_v.color, screen);

    #ifdef RD_DEBUG
    printf("[Point2f] thread: %d vertex: (%f, %f) point: (%d, %d) \n", omp_get_thread_num(), v->x, v->y, p.x, p.y);
    #endif
}
void rdPoint3f(RdVertex3f* v, RdScreen* screen){
    if(v->z > 0){
        RdVertex3f new_v = rdMat4Mul3f(v, rdScale3f);
        new_v = rdMat4Mul3f(&new_v, rdRotate3f);
        new_v = rdMat4Mul3f(&new_v, rdTranslate3f);

        RdScreenPoint p = _rdGetScreenPoint3f(new_v.x, new_v.y, new_v.z, screen);
        _rdSetScreenPoint(&p, new_v.color, screen);

        #ifdef RD_DEBUG
        printf("[Point3f] thread: %d vertex: (%f, %f, %f) point: (%d, %d) \n", omp_get_thread_num(), v->x, v->y, v->z, p.x, p.y);
        #endif
    }
}

void rdLine2f(RdVertex2f* v0, RdVertex2f* v1, RdScreen* screen){
    RdVertex2f new_v0 = rdMat3Mul2f(v0, rdScale2f);
    RdVertex2f new_v1 = rdMat3Mul2f(v1, rdScale2f);

    new_v0 = rdMat3Mul2f(&new_v0, rdRotate2f);
    new_v1 = rdMat3Mul2f(&new_v1, rdRotate2f);

    new_v0 = rdMat3Mul2f(&new_v0, rdTranslate2f);
    new_v1 = rdMat3Mul2f(&new_v1, rdTranslate2f);

    RdScreenPoint p0 = _rdGetScreenPoint2f(new_v0.x, new_v0.y, screen);
    RdScreenPoint p1 = _rdGetScreenPoint2f(new_v1.x, new_v1.y, screen);
   
    _rdLine(&p0, &p1, new_v0.color, new_v1.color, screen);
}
void rdLine3f(RdVertex3f* v0, RdVertex3f* v1, RdScreen* screen){
    RdVertex3f new_v0 = rdMat4Mul3f(v0, rdScale3f);
    RdVertex3f new_v1 = rdMat4Mul3f(v1, rdScale3f);

    new_v0 = rdMat4Mul3f(&new_v0, rdRotate3f);
    new_v1 = rdMat4Mul3f(&new_v1, rdRotate3f);

    new_v0 = rdMat4Mul3f(&new_v0, rdTranslate3f);
    new_v1 = rdMat4Mul3f(&new_v1, rdTranslate3f);

    RdScreenPoint p0 = _rdGetScreenPoint3f(new_v0.x, new_v0.y, new_v0.z, screen);
    RdScreenPoint p1 = _rdGetScreenPoint3f(new_v1.x, new_v1.y, new_v1.z, screen);
   
    _rdLine(&p0, &p1, new_v0.color, new_v1.color, screen);
}

// multiple
void rdPoints2f(RdVertex2f* v, size_t count, RdScreen* screen){
    #pragma omp parallel for schedule(guided)
    for(size_t i = 0; i < count; i++) rdPoint2f(v + i, screen);
}

void rdPoints3f(RdVertex3f* v, size_t count, RdScreen* screen){
    #pragma omp parallel for schedule(guided)
    for(size_t i = 0; i < count; i++) rdPoint3f(v + i, screen);
}

void rdLines2f(RdVertex2f* v, size_t count, RdScreen* screen, RD_LINES option){
    if(option == LINES){
        for(size_t i = 0; i < count; i += 2)
            rdLine2f(v + i, v + i + 1, screen);
    }else if(option == LINE_STRIP){
        for(size_t i = 0; i < count - 1; i++)
            rdLine2f(v + i, v + i + 1, screen);
    }else if(option == LINE_LOOP){
        for(size_t i = 0; i < count; i++){
            if(i < count - 1)
                rdLine2f(v + i, v + i + 1, screen);
            else
                rdLine2f(v + i, v, screen);
        }
    }else if(option == LINES_FULL){
        for(size_t i = 0; i < count; i++)
            for(size_t j = 0; j < count; j++)
                if(i != j) rdLine2f(v + i, v + j, screen);
    }
}
void rdLines3f(RdVertex3f* v, size_t count, RdScreen* screen, RD_LINES option){
    if(option == LINES){
        for(size_t i = 0; i < count; i += 2)
            rdLine3f(v + i, v + i + 1, screen);
    }else if(option == LINE_STRIP){
        for(size_t i = 0; i < count - 1; i++)
            rdLine3f(v + i, v + i + 1, screen);
    }else if(option == LINE_LOOP){
        for(size_t i = 0; i < count; i++){
            if(i < count - 1)
                rdLine3f(v + i, v + i + 1, screen);
            else
                rdLine3f(v + i, v, screen);
        }
    }else if(option == LINES_FULL){
        for(size_t i = 0; i < count; i++)
            for(size_t j = 0; j < count; j++)
                if(i != j) rdLine3f(v + i, v + j, screen);
    }
}
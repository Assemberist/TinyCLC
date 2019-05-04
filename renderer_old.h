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
    int x, y;
} RdScreenPoint;

typedef struct RdIndex2{
    size_t i0, i1;
} RdIndex2;

typedef struct RdIndex3{
    size_t i0, i1, i2;
} RdIndex3;

typedef struct RdProgram2f{
    RdVertex2f(*vertexShader)(RdVertex2f*);
    float(*fragmentShader)(RdScreenPoint*, float);
} RdProgram2f;

typedef struct RdProgram3f{
    RdVertex3f(*vertexShader)(RdVertex3f*);
    float(*fragmentShader)(RdScreenPoint*, float);
} RdProgram3f;

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

int max(int x, int y){
    return x > y ? x : y;
}
int min(int x, int y){
    return x > y ? y : x;
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
    float rad = angle * 3.141592f / 180.0f;
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

    float rad = angle * 3.141592f / 180.0f;
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

void rdDestroyScreen(RdScreen* screen){
    free(screen->buffer);
}

char* _rdGetBufferOffset(RdScreenPoint* p, RdScreen* screen){
    if(p->x < 0 || p->y < 0) return NULL;
    if(p->x >= screen->w || p->y >= screen->h) return NULL;

    char* offset = screen->buffer + p->y * screen->w + p->x;
    return offset;
}

RdScreenPoint _rdGetScreenPoint(float x, float y, RdScreen* screen){
    int _x =  x * (screen->w / screen->viewport->w) / 2 + screen->w / 2;
    int _y = screen->h / 2 - y * (screen->h / screen->viewport->h) / 2;

    if(_x == screen->w) _x--;
    if(_y == screen->h) _y--;
    
    return (RdScreenPoint){_x, _y};
}
RdScreenPoint _rdGetScreenPoint3f(float x, float y, float z, RdScreen* screen){
    float c = screen->viewport->d / z;
    x *= c;
    y *= c;

    int _x =  x * (screen->w / screen->viewport->w) / 2 + screen->w / 2;
    int _y = screen->h / 2 - y * (screen->h / screen->viewport->h) / 2;

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
//                     VIEWPORT
/////////////////////////////////////////////////////
RdViewport rdCreateViewportIdentity(RdScreen* screen){
    float h = 2.0f * screen->h;
    float w = screen->w;

    if(w > h)
        return (RdViewport){1.0f, w / h, 1.0f};
    else
        return (RdViewport){h / w, 1.0f, 1.0f};
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
    rdRender(screen); // render
    printf("\e[%dA", screen->h); // go up
    printf("\e[?25h"); // enable cursor
}

// hidden
void _rdLine(RdScreenPoint* p0, RdScreenPoint* p1, float color0, float color1, float(*fragmentShader)(RdScreenPoint*, float), RdScreen* screen){
    int dx = p1->x - p0->x;
    int dy = p1->y - p0->y;
    size_t max = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float step_x = (float)dx / max;
    float step_y = (float)dy / max;

    float step_color = (color1 - color0) / max;

    #pragma omp parallel for schedule(guided)
    for(size_t i = 0; i <= max; i++){
        RdScreenPoint p = {p0->x + i * step_x, p0->y + i * step_y};
        _rdSetScreenPoint(&p, fragmentShader(&p, color0 + i * step_color), screen);
    }
}

void _rdTriangle(RdScreenPoint* p0, RdScreenPoint* p1, RdScreenPoint* p2, float color0, float color1, float color2, float(*fragmentShader)(RdScreenPoint*, float), RdScreen* screen){
    RdScreenPoint* min = _rdMinScreenPoint(_rdMinScreenPoint(p0, p1, true), p2, true);
    RdScreenPoint* mid = _rdMidScreenPoint(p0, p1, p2, true);
    RdScreenPoint* max = _rdMaxScreenPoint(_rdMaxScreenPoint(p0, p1, true), p2, true);

    int dx0 = mid.x - min.x;
    int dy0 = mid.y - min.y;
    float s0 = (float)dy0 / dx0;

    int dx1 = max.x - min.x;
    int dy1 = max.y - min.y;
    float s1 = (float)dy1 / dx1;

    int dx2 = max.x - mid.x;
    int dy2 = max.y - mid.y;
    float s2 = (float)dy2 / dx2;

    // first triangle
    for(int x = min.x; x <= mid.x; x++){
        int to = s0 > 0 ? s0 * (x - min.x) + min.y : s1 * (x - min.x) + min.y;
        int from = s0 < 0 ? s0 * (x - min.x) + min.y : s1 * (x - min.x) + min.y;
        
        for(int y = from; y <= to; y++)
            _rdSetScreenPoint((RdScreenPoint){x, y}, 1.0f, screen);
    }

    // second triangle
    for(int x = mid.x; x <= max.x; x++){
        int to = s2 > 0 ? s1 * (x - min.x) + min.y : s2 * (x - mid.x) + mid.y;
        int from = s2 < 0 ? s1 * (x - min.x) + min.y : s2 * (x - mid.x) + mid.y;
        
        for(int y = from; y <= to; y++)
            _rdSetScreenPoint((RdScreenPoint){x, y}, 1.0f, screen);   
    }
}

// single
void rdPoint2f(RdVertex2f* v, RdProgram2f* prog, RdScreen* screen){
    RdVertex2f new_v = prog->vertexShader(v);

    RdScreenPoint p = _rdGetScreenPoint(new_v.x, new_v.y, screen);
    _rdSetScreenPoint(&p, prog->fragmentShader(&p, new_v.color), screen);

    #ifdef RD_DEBUG
    printf("[Point2f] thread: %d vertex: (%f, %f) point: (%d, %d) \n", omp_get_thread_num(), v->x, v->y, p.x, p.y);
    #endif
}
void rdPoint3f(RdVertex3f* v, RdProgram3f* prog, RdScreen* screen){
    RdVertex3f new_v =  prog->vertexShader(v);

    if(new_v.z > 0){
        RdScreenPoint p = _rdGetScreenPoint3f(new_v.x, new_v.y, new_v.z, screen);
        _rdSetScreenPoint(&p,  prog->fragmentShader(&p, new_v.color), screen);

        #ifdef RD_DEBUG
        printf("[Point3f] thread: %d vertex: (%f, %f, %f) point: (%d, %d) \n", omp_get_thread_num(), v->x, v->y, v->z, p.x, p.y);
        #endif
    }
}

void rdLine2f(RdVertex2f* v0, RdVertex2f* v1, RdProgram2f* prog, RdScreen* screen){
    RdVertex2f new_v0 = prog->vertexShader(v0);
    RdVertex2f new_v1 = prog->vertexShader(v1);

    RdScreenPoint p0 = _rdGetScreenPoint(new_v0.x, new_v0.y, screen);
    RdScreenPoint p1 = _rdGetScreenPoint(new_v1.x, new_v1.y, screen);
   
    _rdLine(&p0, &p1, new_v0.color, new_v1.color, prog->fragmentShader, screen);
}
void rdLine3f(RdVertex3f* v0, RdVertex3f* v1, RdProgram3f* prog, RdScreen* screen){
    RdVertex3f new_v0 = prog->vertexShader(v0);
    RdVertex3f new_v1 = prog->vertexShader(v1);

    RdScreenPoint p0 = _rdGetScreenPoint3f(new_v0.x, new_v0.y, new_v0.z, screen);
    RdScreenPoint p1 = _rdGetScreenPoint3f(new_v1.x, new_v1.y, new_v1.z, screen);
   
    _rdLine(&p0, &p1, new_v0.color, new_v1.color, prog->fragmentShader, screen);
}

void rdTriangle2f(RdVertex2f* v0, RdVertex2f* v1, RdVertex2f* v2, RdProgram2f* prog, RdScreen* screen){
    RdVertex2f new_v0 = prog->vertexShader(v0);
    RdVertex2f new_v1 = prog->vertexShader(v1);
    RdVertex2f new_v2 = prog->vertexShader(v2);

    RdScreenPoint p0 = _rdGetScreenPoint(new_v0.x, new_v0.y, screen);
    RdScreenPoint p1 = _rdGetScreenPoint(new_v1.x, new_v1.y, screen);
    RdScreenPoint p2 = _rdGetScreenPoint(new_v2.x, new_v2.y, screen);

    _rdTriangle(&p0, &p1, &p2, new_v0.color, new_v1.color, new_v2.color, prog->fragmentShader, screen);
}

// // multiple
void rdPoints2f(RdVertex2f* verts, size_t count, RdProgram2f* prog, RdScreen* screen){
    #pragma omp parallel for schedule(guided)
    for(size_t i = 0; i < count; i++) rdPoint2f(verts + i, prog, screen);
}

void rdPoints3f(RdVertex3f* verts, size_t count, RdProgram3f* prog, RdScreen* screen){
    #pragma omp parallel for schedule(guided)
    for(size_t i = 0; i < count; i++) rdPoint3f(verts + i, prog, screen);
}

void rdLines2f(RdVertex2f* verts, RdIndex2* indexes, size_t indexes_count, RdProgram2f* prog, RdScreen* screen){
    for(size_t i = 0; i < indexes_count; i++)
        rdLine2f(verts + indexes[i].i0, verts + indexes[i].i1, prog, screen);
}
void rdLines3f(RdVertex3f* verts, RdIndex2* indexes, size_t indexes_count, RdProgram3f* prog, RdScreen* screen){
    for(size_t i = 0; i < indexes_count; i++)
        rdLine3f(verts + indexes[i].i0, verts + indexes[i].i1, prog, screen);
}
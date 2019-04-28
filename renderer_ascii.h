#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct RdVertex2f{
    float x, y, color;
} RdVertex2f;

typedef struct RdVertex3f{
    float x, y, z, color;
} RdVertex3f;

typedef struct RdScreen{
    size_t h, w, total;
    char* buffer;
} RdScreen;


// screen
RdScreen rdCreateScreen(size_t w, size_t h){
    RdScreen result = {.h = h, .w = w, .total = h * w};
    result.buffer = malloc(h * w);

    return result;
}

void rdDestroyScreen(RdScreen* screen){
    free(screen->buffer);
}

// utils
char _rdGetColor(float color){
    return (char)(color);
}

char* _rdGetPixel(float x, float y, RdScreen* screen){
    size_t _x =  (x + 1) * screen->w / 2;
    size_t _y = (y + 1) * screen->h / 2;
    size_t offset = _y * screen->w + _x;

    if(_x < screen->w && _y < screen->h) return screen->buffer + offset;
    return NULL;
}

// render
void rdVertex2f(RdVertex2f* v, RdScreen* screen){
    char* offset = _rdGetPixel(v->x, v->y, screen);
    if(offset) *offset = _rdGetColor(v->color);
}

void rdLine2f(RdVertex2f* v0, RdVertex2f* v1, RdScreen* screen){
    float step_x = 2.0f / (float)screen->w;
    

    if(v0->x > v1->x){
        RdVertex2f* temp = v0;
        v0 = v1;
        v1 = temp;
    }

    float s = (v1->y - v0->y) / (v1->x - v0->x);
    float s_color = (v1->color - v0->color) / (v1->x - v0->x);

    char* offset = NULL;

    for(float x = v0->x; x <= v1->x; x+= 0.01f){
        offset = _rdGetPixel(x, s * (x - v0->x) + v0->y, screen);
        if(!offset) return;
        *offset = _rdGetColor(s_color * (x - v0->x) + v0->color);
    }
}

void rdClear(RdScreen* screen){
    memset(screen->buffer, '.', screen->total);
}

void rdRender(RdScreen* screen){
    printf("\e[1;1H\e[2J");

    char pixdist[] = " ";
    for(size_t i = 0; i < screen->h; i++){
        for(size_t j = 0; j < screen->w; j++) printf("%c%s", screen->buffer[i * screen->w + j], pixdist);
        puts("");
    }
}
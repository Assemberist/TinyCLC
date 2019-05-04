#pragma once
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef auto
#define auto __auto_type
#endif

// definitions
#ifndef __cat
#define __cat(X, Y) X##Y
#endif

#ifndef _cat
#define _cat(X, Y) __cat(X, Y)
#endif


#define _vec(dim, T) _vec##dim##_##T

#define vec2(T) _vec(2, T)
#define vec3(T) _vec(3, T)
#define vec4(T) _vec(4, T)

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
T _cat(vec2(T), vec2(T))(const vec2(T)* v0, const vec2(T)* v1){\
    return v0->x * v1->x + v0->y * v1->y;\
}\
vec2(T) _cat(vec2(T), mat2)(const vec2(T)* v, T m[2][2]){\
    vec2(T) result;\
    result.x = v->x * m[0][0] + v->y * m[1][0];\
    result.y = v->x * m[0][1] + v->y * m[1][1];\
    return result;\
}\
vec2(T) _cat(mat2, vec2(T))(const vec2(T)* v, T m[2][2]){\
    vec2(T) result;\
    result.x = m[0][0] * v->x + m[0][1]* v->y;\
    result.y = m[1][0] * v->x + m[1][1] * v->y;\
    return result;\
}\
T _cat(vec3(T), vec3(T))(const vec3(T)* v0, const vec3(T)* v1){\
    return v0->x * v1->x + v0->y * v1->y + v0->z * v1->z;\
}\
vec3(T) _cat(vec3(T), mat3)(const vec3(T)* v, T m[3][3]){\
    vec3(T) result;\
    result.x = v->x * m[0][0] + v->y * m[1][0] + v->z * m[2][0];\
    result.y = v->x * m[0][1] + v->y * m[1][1] + v->z * m[2][1];\
    result.z = v->x * m[0][2] + v->y * m[1][2] + v->z * m[2][2];\
    return result;\
}\
vec3(T) _cat(mat3, vec3(T))(const vec3(T)* v, T m[3][3]){\
    vec3(T) result;\
    result.x = m[0][0] * v->x + m[0][1] * v->y + m[0][2] * v->z;\
    result.y = m[1][0] * v->x + m[1][1] * v->y + m[1][2] * v->z;\
    result.z = m[2][0] * v->x + m[2][1] * v->y + m[2][2] * v->z;\
    return result;\
}\
T _cat(vec3(T), vec2(T))(const vec3(T)* v0, const vec2(T)* v1){\
    vec3(T) temp = {v1->x, v1->y, 1};\
    return vec3vec3(T)(v0, &temp);\
}\
vec3(T) _cat(vec2(T), mat3)(const vec2(T)* v, T m[3][3]){\
    vec3(T) temp = {v->x, v->y, 1};\
    return vec3mat3(T)(&temp, m);\
}\
vec3(T) _cat(mat3, vec2(T))(const vec2(T)* v, T m[3][3]){\
    vec3(T) temp = {v->x, v->y, 1};\
    return mat3vec3(T)(&temp, m);\
}\
T _cat(vec4(T), vec4(T))(const vec4(T)* v0, const vec4(T)* v1){\
    return v0->x * v1->x + v0->y * v1->y + v0->z * v1->z + v0->w * v1->w;\
}\
vec4(T) _cat(vec4(T), mat4)(const vec4(T)* v, T m[4][4]){\
    vec4(T) result;\
    result.x = v->x * m[0][0] + v->y * m[1][0] + v->z * m[2][0] + v->w * m[3][0];\
    result.y = v->x * m[0][1] + v->y * m[1][1] + v->z * m[2][1] + v->w * m[3][1];\
    result.z = v->x * m[0][2] + v->y * m[1][2] + v->z * m[2][2] + v->w * m[3][2];\
    result.w = v->x * m[0][3] + v->y * m[1][3] + v->z * m[2][3] + v->w * m[3][3];\
    return result;\
}\
vec4(T) _cat(mat4, vec4(T))(const vec4(T)* v, T m[4][4]){\
    vec4(T) result;\
    result.x = m[0][0] * v->x + m[0][1] * v->y + m[0][2] * v->z + m[0][3] * v->w;\
    result.y = m[1][0] * v->x + m[1][1] * v->y + m[1][2] * v->z + m[1][3] * v->w;\
    result.z = m[2][0] * v->x + m[2][1] * v->y + m[2][2] * v->z + m[2][3] * v->w;\
    result.w = m[3][0] * v->x + m[3][1] * v->y + m[3][2] * v->z + m[3][3] * v->w;\
    return result;\
}\
T _cat(vec4(T), vec3(T))(const vec4(T)* v0, const vec3(T)* v1){\
    vec4(T) temp = {v1->x, v1->y, v1->z, 1};\
    return vec4vec4(T)(v0, &temp);\
}\
vec4(T) _cat(vec3(T), mat4)(const vec3(T)* v, T m[4][4]){\
    vec4(T) temp = {v->x, v->y, v->z, 1};\
    return vec4mat4(T)(&temp, m);\
}\
vec4(T) _cat(mat4, vec3(T))(const vec3(T)* v, T m[4][4]){\
    vec4(T) temp = {v->x, v->y, v->z, 1};\
    return mat4vec4(T)(&temp, m);\
}


// methods
#define vec2vec2(T) _cat(vec2(T), vec2(T))
#define vec2mat2(T) _cat(vec2(T), mat2)
#define mat2vec2(T) _cat(mat2, vec2(T))

#define vec3vec3(T) _cat(vec3(T), vec3(T))
#define vec3mat3(T) _cat(vec3(T), mat3)
#define mat3vec3(T) _cat(mat3, vec3(T))

#define vec3vec2(T) _cat(vec3(T), vec2(T))
#define vec2vec3(T) _cat(vec3(T), vec2(T))
#define vec2mat3(T) _cat(vec2(T), mat3)
#define mat3vec2(T) _cat(mat3, vec2(T))

#define vec4vec4(T) _cat(vec4(T), vec4(T))
#define vec4mat4(T) _cat(vec4(T), mat4)
#define mat4vec4(T) _cat(mat4, vec4(T))

#define vec4vec3(T) _cat(vec4(T), vec3(T))
#define vec3vec4(T) _cat(vec4(T), vec3(T))
#define vec3mat4(T) _cat(vec3(T), mat4)
#define mat4vec3(T) _cat(mat4, vec3(T))

// types (std)
#ifndef STD_ARRAY_DONT_USE_PREDEFINED_TYPES

typedef unsigned char unsigned_char;
typedef unsigned short unsigned_short;
typedef unsigned int unsigned_int;
typedef unsigned long int unsigned_long_int;
typedef unsigned long long int unsigned_long_long_int; 
typedef unsigned long unsigned_long; 
typedef long int long_int;
typedef long long int long_long_int;
typedef long double long_double;

LINEAR(unsigned_char)
LINEAR(unsigned_short)
LINEAR(unsigned_int)
LINEAR(unsigned_long_int)
LINEAR(unsigned_long)
LINEAR(unsigned_long_long_int)
LINEAR(char)
LINEAR(short)
LINEAR(int)
LINEAR(long_int)
LINEAR(long_long_int)
LINEAR(long)

LINEAR(float)
LINEAR(double)
LINEAR(long_double)

// types (stddef)
LINEAR(size_t)
LINEAR(ptrdiff_t)
LINEAR(wchar_t)

// types (stdint)
LINEAR(int_least8_t)
LINEAR(int_least16_t)
LINEAR(int_least32_t)
LINEAR(int_least64_t)
LINEAR(uint_least8_t)
LINEAR(uint_least16_t)
LINEAR(uint_least32_t)
LINEAR(uint_least64_t)
LINEAR(int_fast8_t)
LINEAR(int_fast16_t)
LINEAR(int_fast32_t)
LINEAR(int_fast64_t)
LINEAR(uint_fast8_t)
LINEAR(uint_fast16_t)
LINEAR(uint_fast32_t)
LINEAR(uint_fast64_t)

LINEAR(int8_t)
LINEAR(int16_t)
LINEAR(int32_t)
LINEAR(int64_t)
LINEAR(uint8_t)
LINEAR(uint16_t)
LINEAR(uint32_t)
LINEAR(uint64_t)

LINEAR(bool)

#endif
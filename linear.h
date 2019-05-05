#pragma once
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

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
vec2(T) _cat(_cat(vec2(T), _add_), vec2(T))(const vec2(T) v0, const vec2(T) v1){\
    return (vec2(T)){v0.x + v1.x, v0.y + v1.y};\
}\
vec2(T) _cat(_cat(vec2(T), _sub_), vec2(T))(const vec2(T) v0, const vec2(T) v1){\
    return (vec2(T)){v0.x - v1.x, v0.y - v1.y};\
}\
vec2(T) _cat(_cat(vec2(T), _hadmul_), vec2(T))(const vec2(T) v0, const vec2(T) v1){\
    return (vec2(T)){v0.x * v1.x, v0.y * v1.y};\
}\
vec2(T) _cat(_cat(vec2(T), _haddiv_), vec2(T))(const vec2(T) v0, const vec2(T) v1){\
    return (vec2(T)){v0.x / v1.x, v0.y / v1.y};\
}\
T _cat(_cat(vec2(T), _mul_), vec2(T))(const vec2(T) v0, const vec2(T) v1){\
    return v0.x * v1.x + v0.y * v1.y;\
}\
vec2(T) _cat(_cat(vec2(T), _mul_), mat2(T))(const vec2(T) v, const mat2(T)* m){\
    vec2(T) result;\
    result.x = v.x * m->m[0][0] + v.y * m->m[1][0];\
    result.y = v.x * m->m[0][1] + v.y * m->m[1][1];\
    return result;\
}\
vec2(T) _cat(_cat(mat2(T), _mul_), vec2(T))(const vec2(T) v, const mat2(T)* m){\
    vec2(T) result;\
    result.x = m->m[0][0] * v.x + m->m[0][1]* v.y;\
    result.y = m->m[1][0] * v.x + m->m[1][1] * v.y;\
    return result;\
}\
mat2(T) _cat(_cat(mat2(T), _add_), mat2(T))(const mat2(T)* m0, const mat2(T)* m1){\
    mat2(T) result;\
    result.m[0][0] = m0->m[0][0] + m1->m[0][0];\
    result.m[0][1] = m0->m[0][1] + m1->m[0][1];\
    result.m[1][0] = m0->m[1][0] + m1->m[1][0];\
    result.m[1][1] = m0->m[1][1] + m1->m[1][1];\
    return result;\
}\
mat2(T) _cat(_cat(mat2(T), _sub_), mat2(T))(const mat2(T)* m0, const mat2(T)* m1){\
    mat2(T) result;\
    result.m[0][0] = m0->m[0][0] - m1->m[0][0];\
    result.m[0][1] = m0->m[0][1] - m1->m[0][1];\
    result.m[1][0] = m0->m[1][0] - m1->m[1][0];\
    result.m[1][1] = m0->m[1][1] - m1->m[1][1];\
    return result;\
}\
mat2(T) _cat(_cat(mat2(T), _hadmul_), mat2(T))(const mat2(T)* m0, const mat2(T)* m1){\
    mat2(T) result;\
    result.m[0][0] = m0->m[0][0] * m1->m[0][0];\
    result.m[0][1] = m0->m[0][1] * m1->m[0][1];\
    result.m[1][0] = m0->m[1][0] * m1->m[1][0];\
    result.m[1][1] = m0->m[1][1] * m1->m[1][1];\
    return result;\
}\
mat2(T) _cat(_cat(mat2(T), _haddiv_), mat2(T))(const mat2(T)* m0, const mat2(T)* m1){\
    mat2(T) result;\
    result.m[0][0] = m0->m[0][0] / m1->m[0][0];\
    result.m[0][1] = m0->m[0][1] / m1->m[0][1];\
    result.m[1][0] = m0->m[1][0] / m1->m[1][0];\
    result.m[1][1] = m0->m[1][1] / m1->m[1][1];\
    return result;\
}\
mat2(T) _cat(_cat(mat2(T), _mul_), mat2(T))(const mat2(T)* m0, const mat2(T)* m1){\
    mat2(T) result;\
    result.m[0][0] = m0->m[0][0] * m1->m[0][0] + m0->m[0][1] * m1->m[1][0];\
    result.m[0][1] = m0->m[0][0] * m1->m[0][1] + m0->m[0][1] * m1->m[1][1];\
    result.m[1][0] = m0->m[1][0] * m1->m[0][0] + m0->m[1][1] * m1->m[1][0];\
    result.m[1][1] = m0->m[1][0] * m1->m[0][1] + m0->m[1][1] * m1->m[1][1];\
    return result;\
}\
mat2(T) _cat(mat2(T), _mul_scalar_)(const mat2(T)* m, T val){\
    mat2(T) result;\
    result.m[0][0] = m->m[0][0] * val;\
    result.m[0][1] = m->m[0][1] * val;\
    result.m[1][0] = m->m[1][0] * val;\
    result.m[1][1] = m->m[1][1] * val;\
    return result;\
}\
mat2(T) _cat(mat2(T), _inverse_)(const mat2(T)* m){\
    mat2(T) result;\
    T det = (T)1 / (m->m[0][0] * m->m[1][1] - m->m[1][0] * m->m[0][1]);\
    result.m[0][0] = m->m[1][1];\
    result.m[0][1] = -m->m[0][1];\
    result.m[1][0] = -m->m[1][0];\
    result.m[1][1] = m->m[0][0];\
    return mat2_mul_scalar(T)(&result, det);\
}\
mat2(T) _cat(_cat(mat2(T), _div_), mat2(T))(const mat2(T)* m0, const mat2(T)* m1){\
    mat2(T) temp = mat2_inverse(T)(m1);\
    return mat2_mul_mat2(T)(m0, &temp);\
}\
vec2(T) _cat(_lininter_, T)(const vec2(T) x, const vec2(T) y){\
    mat2(T) temp0 = {{\
        {x.x, x.y},\
        {1, 1}\
    }};\
    mat2(T) temp = mat2_inverse(T)(&temp0);\
    return vec2_mul_mat2(T)(y, &temp);\
}\
T _cat(vec3(T), vec3(T))(const vec3(T) v0, const vec3(T) v1){\
    return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z;\
}\
vec3(T) _cat(vec3(T), mat3(T))(const vec3(T) v, const mat3(T)* m){\
    vec3(T) result;\
    result.x = v.x * m->m[0][0] + v.y * m->m[1][0] + v.z * m->m[2][0];\
    result.y = v.x * m->m[0][1] + v.y * m->m[1][1] + v.z * m->m[2][1];\
    result.z = v.x * m->m[0][2] + v.y * m->m[1][2] + v.z * m->m[2][2];\
    return result;\
}\
vec3(T) _cat(mat3(T), vec3(T))(const vec3(T) v, const mat3(T)* m){\
    vec3(T) result;\
    result.x = m->m[0][0] * v.x + m->m[0][1] * v.y + m->m[0][2] * v.z;\
    result.y = m->m[1][0] * v.x + m->m[1][1] * v.y + m->m[1][2] * v.z;\
    result.z = m->m[2][0] * v.x + m->m[2][1] * v.y + m->m[2][2] * v.z;\
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
T _cat(vec4(T), vec4(T))(const vec4(T) v0, const vec4(T) v1){\
    return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z + v0.w * v1.w;\
}\
vec4(T) _cat(vec4(T), mat4(T))(const vec4(T) v, const mat4(T)* m){\
    vec4(T) result;\
    result.x = v.x * m->m[0][0] + v.y * m->m[1][0] + v.z * m->m[2][0] + v.w * m->m[3][0];\
    result.y = v.x * m->m[0][1] + v.y * m->m[1][1] + v.z * m->m[2][1] + v.w * m->m[3][1];\
    result.z = v.x * m->m[0][2] + v.y * m->m[1][2] + v.z * m->m[2][2] + v.w * m->m[3][2];\
    result.w = v.x * m->m[0][3] + v.y * m->m[1][3] + v.z * m->m[2][3] + v.w * m->m[3][3];\
    return result;\
}\
vec4(T) _cat(mat4(T), vec4(T))(const vec4(T) v, const mat4(T)* m){\
    vec4(T) result;\
    result.x = m->m[0][0] * v.x + m->m[0][1] * v.y + m->m[0][2] * v.z + m->m[0][3] * v.w;\
    result.y = m->m[1][0] * v.x + m->m[1][1] * v.y + m->m[1][2] * v.z + m->m[1][3] * v.w;\
    result.z = m->m[2][0] * v.x + m->m[2][1] * v.y + m->m[2][2] * v.z + m->m[2][3] * v.w;\
    result.w = m->m[3][0] * v.x + m->m[3][1] * v.y + m->m[3][2] * v.z + m->m[3][3] * v.w;\
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
}


// methods
#define vec2_add_vec2(T) _cat(_cat(vec2(T), _add_), vec2(T))
#define vec2_sub_vec2(T) _cat(_cat(vec2(T), _sub_), vec2(T))
#define vec2_hadmul_vec2(T) _cat(_cat(vec2(T), _hadmul_), vec2(T))
#define vec2_haddiv_vec2(T) _cat(_cat(vec2(T), _haddiv_), vec2(T))
#define vec2_mul_vec2(T) _cat(_cat(vec2(T), _mul_), vec2(T))
#define vec2_mul_mat2(T) _cat(_cat(vec2(T), _mul_), mat2(T))
#define mat2_mul_vec2(T) _cat(_cat(mat2(T), _mul_), vec2(T))
#define mat2_add_mat2(T) _cat(_cat(mat2(T), _add_), mat2(T))
#define mat2_sub_mat2(T) _cat(_cat(mat2(T), _sub_), mat2(T))
#define mat2_hadmul_mat2(T) _cat(_cat(mat2(T), _hadmul_), mat2(T))
#define mat2_haddiv_mat2(T) _cat(_cat(mat2(T), _haddiv_), mat2(T))
#define mat2_mul_mat2(T) _cat(_cat(mat2(T), _mul_), mat2(T))
#define mat2_mul_scalar(T) _cat(mat2(T), _mul_scalar_)
#define mat2_inverse(T) _cat(mat2(T), _inverse_)
#define mat2_div_mat2(T) _cat(_cat(mat2(T), _div_), mat2(T))
#define lininter(T) _cat(_lininter_, T)

#define vec3vec3(T) _cat(vec3(T), vec3(T))
#define vec3mat3(T) _cat(vec3(T), mat3(T))
#define mat3vec3(T) _cat(mat3(T), vec3(T))
#define mat3mat3(T) _cat(mat3(T), mat3(T))

#define vec4vec4(T) _cat(vec4(T), vec4(T))
#define vec4mat4(T) _cat(vec4(T), mat4(T))
#define mat4vec4(T) _cat(mat4(T), vec4(T))
#define mat4mat4(T) _cat(mat4(T), mat4(T))


#define mat2_identity(T) (mat2(T)){{\
    {1, 0},\
    {0, 1}\
}}
#define mat3_identity(T) (mat3(T)){{\
    {1, 0, 0},\
    {0, 1, 0},\
    {0, 0, 1}\
}}
#define mat4_identity(T) (mat4(T)){{\
    {1, 0, 0, 0},\
    {0, 1, 0, 0},\
    {0, 0, 1, 0},\
    {0, 0, 0, 1}\
}}

// types (std)
#ifndef LINEAR_DONT_USE_PREDEFINED_TYPES

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
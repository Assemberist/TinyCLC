#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef STD_VECTOR_CAPACITY_GROW
#define STD_VECTOR_CAPACITY_GROW 1.618
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
#define std_vector(T) _cat(_std_vector_, T)

#define USE_VECTOR(T) struct _cat(func_, std_vector(T));\
typedef struct std_vector(T){\
    size_t _size, _capacity;\
    T* _data;\
	struct _cat(func_, std_vector(T))* funcs;\
}std_vector(T);\
typedef struct _cat(func_, std_vector(T)){\
    void (*reserve)(struct std_vector(T)*, size_t);\
    void (*destruct)(struct std_vector(T)*);\
    void (*clear)(struct std_vector(T)*);\
    size_t (*size)(struct std_vector(T)*);\
    size_t (*capacity)(struct std_vector(T)*);\
    const T*(*data)(struct std_vector(T)*);\
    T* (*at)(struct std_vector(T)*, size_t);\
    T* (*begin)(struct std_vector(T)*);\
    T* (*end)(struct std_vector(T)*);\
    T* (*back)(struct std_vector(T)*);\
    void (*push_back)(struct std_vector(T)*, T);\
    T (*pop_back)(struct std_vector(T)*);\
} _cat(func_, std_vector(T));\
typedef T* _cat(_iter, std_vector(T));\
void _cat(_reserve, std_vector(T))(std_vector(T)* vec, size_t size){\
    vec->_capacity = size > 1 ? size : 2;\
    vec->_data = malloc(size * sizeof(T));\
    if(!vec->_data){\
        fprintf(stderr, "std::vector [malloc]: not enough memory\n");\
        exit(EXIT_FAILURE);\
    }\
}\
void _cat(_destruct, std_vector(T))(std_vector(T)* vec){\
    vec->_capacity = 0;\
    vec->_size = 0;\
    free(vec->_data);\
    vec->_data = NULL;\
}\
void _cat(_clear, std_vector(T))(std_vector(T)* vec){\
    vec->_size = 0;\
}\
T* _cat(_at, std_vector(T))(std_vector(T)* vec, size_t index){\
    if(index >= vec->_size){\
        fprintf(stderr, "std::vector [at]: index %d is out of bounds\n", index);\
        exit(EXIT_FAILURE);\
    }\
    return &vec->_data[index];\
}\
size_t _cat(_size, std_vector(T))(std_vector(T)* vec){\
    return vec->_size;\
}\
size_t _cat(_capacity, std_vector(T))(std_vector(T)* vec){\
    return vec->_capacity;\
}\
const T* _cat(_data, std_vector(T))(std_vector(T)* vec){\
    return vec->_data;\
}\
T* _cat(_begin, std_vector(T))(std_vector(T)* vec){\
    return vec->_data;\
}\
T* _cat(_end, std_vector(T))(std_vector(T)* vec){\
    return vec->_data + vec->_size;\
}\
T* _cat(_back, std_vector(T))(std_vector(T)* vec){\
    return vec->_data + vec->_size - 1;\
}\
void _cat(_push_back, std_vector(T))(std_vector(T)* vec, T value){\
    if(vec->_capacity == 0) vec->funcs->reserve(vec, 2);\
    vec->_size++;\
    if(vec->_size > vec->_capacity){\
        vec->_capacity *= STD_VECTOR_CAPACITY_GROW;\
        vec->_data = realloc(vec->_data, vec->_capacity * sizeof(T));\
        if(!vec->_data){\
            fprintf(stderr, "std::vector [realloc]: not enough memory\n");\
            exit(EXIT_FAILURE);\
        }\
    }\
    *vec->funcs->back(vec) = value;\
}\
T _cat(_pop_back, std_vector(T))(std_vector(T)* vec){\
    T result = *vec->funcs->back(vec);\
    vec->_size--;\
    return result;\
}\
_cat(func_, std_vector(T)) _cat(vfuncs_, std_vector(T))={\
    _cat(_reserve, std_vector(T)), \
    _cat(_destruct, std_vector(T)), \
    _cat(_clear, std_vector(T)), \
    _cat(_size, std_vector(T)), \
    _cat(_capacity, std_vector(T)), \
    _cat(_data, std_vector(T)), \
    _cat(_at, std_vector(T)), \
    _cat(_begin, std_vector(T)), \
    _cat(_end, std_vector(T)), \
    _cat(_back, std_vector(T)), \
    _cat(_push_back, std_vector(T)), \
    _cat(_pop_back, std_vector(T))\
};
// methods
#define std_vector_iterator(T) _cat(_iter, std_vector(T))

#ifndef std_reserve
#define std_reserve(CONTAINER, VAL) (CONTAINER).funcs->reserve(&(CONTAINER), VAL)
#endif

#ifndef std_push_back
#define std_push_back(CONTAINER, VAL) (CONTAINER).funcs->push_back(&(CONTAINER), VAL)
#endif

#ifndef std_destruct
#define std_desturct(CONTAINER) (CONTAINER).funcs->begin(&(CONTAINER))
#endif

#ifndef std_begin
#define std_begin(CONTAINER) (CONTAINER).funcs->begin(&(CONTAINER))
#endif

#ifndef std_end
#define std_end(CONTAINER) (CONTAINER).funcs->.end(&(CONTAINER))
#endif

#ifndef std_back
#define std_back(CONTAINER) (CONTAINER).funcs->back(&(CONTAINER))
#endif

#ifndef std_swap
#define std_swap(ITER1, ITER2) ((*ITER2) = ((*ITER1) + (*ITER2)) - ((*ITER1) = (*ITER2)))
#endif

#ifndef foreach
#define foreach(CONTAINER) for(__typeof__(std_begin(CONTAINER)) it = std_begin(CONTAINER);\
it < std_end(CONTAINER);\
it++)
#endif

#define std_vector_default(T, name) std_vector(T) name ={0, 0, NULL, &_cat(vfuncs_, std_vector(T))}

#pragma once

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

// definitions
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
#define std_swap(ITER1, ITER2) ((*ITER2) = ((*ITER1) + (*ITER2)) - ((*ITER1) = (*ITER2)))
#endif


#define ALGOS(T)\
void _cat(_std_for_each, T)(_cat(_iter, T) begin, _cat(_iter, T) end, void (*func)(_cat(_iter, T) it)){\
    for(_cat(_iter, T) it = begin; it < end; it++) func(it);\
}\
void _cat(_std_bubble_sort, T)(_cat(_iter, T) begin, _cat(_iter, T) end){\
    bool sorted = false;\
    while(!sorted){\
        sorted = true;\
        for(_cat(_iter, T) it = begin; it < end; it++){\
            if(it != end - 1){\
                auto next = it + 1;\
                if(*next < *it){\
                    std_swap(next, it);\
                    sorted = false;\
                }\
            }\
        }\
    }\
}

#define std_for_each(T) _cat(_std_for_each, T)
#define std_bubble_sort(T) _cat(_std_bubble_sort, T)
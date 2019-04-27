#include <stdio.h>
#include "array.h"
#include "algorithm.h"

void foo(std_array_iterator(int) it){
    *it = rand() % 10;
}

ALGOS(std_array(int))

int main()
{
    std_array(int) a = construct_std_array(int, 5);

    std_for_each(std_array(int))(std_begin(a), std_end(a), foo);

    foreach(a)
        printf("%d\n", *it);

    return 0;
}
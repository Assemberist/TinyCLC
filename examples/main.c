#include <stdio.h>
#include "small_vector.h"

int main()
{
    std_small_vector(int) a = construct_std_small_vector(int);

    a.push_back(&a, 5);
    a.push_back(&a, 3);
    a.push_back(&a, 7);
    a.push_back(&a, 4);
    int backed = a.pop_back(&a);

    foreach(a)
        printf("%d\n", *it);
    
    printf("backed %d\n", backed);

    return 0;
}
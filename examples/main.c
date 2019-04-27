#include <stdio.h>
#include "vector.h"


int main()
{
    std_vector(int) v = construct_std_vector(int);
    v.reserve(&v, 1);

    printf("capacity: %d\n", v.capacity(&v));

    return 0;
}
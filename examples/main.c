#include <stdio.h>
#include "vector.h"


int main()
{
    std_vector(int) v = std_vector_default(int);
    v.reserve(&v, 1);

    printf("capacity: %d\n", v.capacity(&v));

    v.destruct(&v);

    return 0;
}
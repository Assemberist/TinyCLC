#include <stdio.h>
#include "vector.h"

int main()
{
    std_vector(int) vec = construct_std_vector(int);

    for(size_t i = 0; i < 100; i++){
        vec.push_back(&vec, 0);
        printf("size: %d capacity: %d\n", vec.size(&vec), vec.capacity(&vec));
    }

    vec.destruct(&vec);

    return 0;
}
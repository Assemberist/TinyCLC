#include <stdio.h>
#include "vector.h"
#include "array.h"

VECTORS(std_array(int))

int main()
{
    std_vector(std_array(int)) v = std_vector_default(std_array(int));
    
    std_array(int) temp = std_array_default(int, 5);

    for(size_t i = 0; i < 100; i++) v.push_back(&v, temp);

    v.destruct(&v);

    return 0;
}
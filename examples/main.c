#include <stdio.h>
#include "vector.h"
#include "pair.h"
#include "array.h"


VECTORS(std_array(int))

int main()
{
    std_vector(std_array(int)) a = std_vector_default(std_array(int));
    a.reserve(&a, 2);

    std_array(int) a0 = std_array_default(int);
    std_array(int) a1 = std_array_default(int);

    a.push_back(&a, a0);
    a.push_back(&a, a1);

    a.destroy(&a);

    return 0;
}
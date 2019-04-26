#include <stdio.h>
#include "array.h"
#include "vector.h"


int main()
{
    std_array(int) a = std_array_default(int);
    std_vector(int) b = std_vector_default(int);

    // init
    a.size = 5;
    b.reserve(&b, 5);

    // fill
    foreach(a) *it = 5;
    foreach(b) *it = 5;

    b.push_back(&b, 4);
    b.push_back(&b, 7);
    int backed = b.pop_back(&b);

    //output
    foreach(a) printf("%d ", *it);
    puts("");

    foreach(b) printf("%d ", *it);
    puts("");

    printf("backed %d\n", backed);

    return 0;
}
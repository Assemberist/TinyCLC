#include <stdio.h>
#include "array.h"
#include "vector.h"

int main()
{
    std_array(int) a = std_array_default(int);
    std_vector(int) b = std_vector_default(int);

    // init
    a.size = 3;
    b.reserve(&b, 3);

    // fill
    foreach(a) *it = 5;

    b.push_back(&b, 5);
    b.push_back(&b, 5);
    b.push_back(&b, 5);
    b.push_back(&b, 7);
    int backed = b.pop_back(&b);

    //output
    foreach(a) printf("%d ", *it);
    puts("");

    foreach(b) printf("%d ", *it);
    puts("");

    printf("backed %d\n", backed);

    // free
    b.destroy(&b);

    return 0;
}
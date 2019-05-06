#include <stdio.h>
#include <time.h>

#define LINEAR_DONT_USE_PREDEFINED_TYPES
#include "linear.h"

LINEAR(float)

int main(int argc, char* argv[]){
    vec3(float) a = {1, 2, 3};
    vec3(float) b = {-4, 5, 6};
    auto c = vec3_cross_vec3(float)(a, b);

    printf("%f %f %f\n", c.x, c.y, c.z);

    return 0;
}
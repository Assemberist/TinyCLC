#include <stdio.h>
#include <time.h>

#define LINEAR_DONT_USE_PREDEFINED_TYPES
#include "linear.h"

LINEAR(float)

int main(){
    vec3(float) x = {0, 1, 2};
    vec3(float) y = {-1, 0, 2};
    vec3(float) z = {-5, 3, 4};

    vec3(float) f = lininter2(float)(x, y, z);

    for(float x = 0; x <= 2; x++){
        for(float y = -1; y <= 2; y++){
            float z = vec3_mul_vec3(float)((vec3(float)){x, y, 1}, f);
            printf("%f\n", z);
        }
    }

    return 0;
}
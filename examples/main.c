#include <stdio.h>
#include <time.h>

#define LINEAR_DONT_USE_PREDEFINED_TYPES
#include "linear.h"

LINEAR(float)

int main(){
    mat2(float) A = {{
        {1, 2},
        {3, 4}
    }};
    mat2(float) B = {{
        {5, 6},
        {7, 8}
    }};

    auto C = mat2_div_mat2(float)(&A, &B);
    printf("%f %f\n%f %f\n",
        C.m[0][0], C.m[0][1],
        C.m[1][0], C.m[1][1]
    );

    return 0;
}
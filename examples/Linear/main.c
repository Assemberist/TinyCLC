#include <stdio.h>
#include <time.h>

#define LINEAR_DONT_USE_PREDEFINED_TYPES
#include "linear.h"

LINEAR(float)

int main(int argc, char* argv[]){
    mat3(float) A = {{
        {1, 2, 3},
        {-4, 5, 6},
        {7, -8, 9}
    }};
    auto B = mat3_inverse(float)(&A);

    printf("%f %f %f\n%f %f %f\n%f %f %f\n", 
        B.m[0][0], B.m[0][1], B.m[0][2],
        B.m[1][0], B.m[1][1], B.m[1][2],
        B.m[2][0], B.m[2][1], B.m[2][2]
    );
    

    return 0;
}
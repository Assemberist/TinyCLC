#include <stdio.h>
#include <time.h>
#include "linear.h"


int main(int argc, char* argv[]){
    mat4(float) m0 = {{
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    }};
    mat4(float) m1 = {{
        {17, 18, 19, 20},
        {21, 22, 23, 24},
        {25, 26, 27, 28},
        {29, 30, 31, 32}
    }};
    mat4(float) m2 = mat4mat4(float)(&m0, &m1);

    printf("%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n",
        m2.m[0][0], m2.m[0][1], m2.m[0][2], m2.m[0][3],
        m2.m[1][0], m2.m[1][1], m2.m[1][2], m2.m[1][3],
        m2.m[2][0], m2.m[2][1], m2.m[2][2], m2.m[2][3],
        m2.m[3][0], m2.m[3][1], m2.m[3][2], m2.m[3][3]
    );

    return 0;
}
#include <stdio.h>
#include <time.h>
#include "linear.h"


// RdVertex2f vShader(RdVertex2f* v){
//     RdVertex2f result = rdMat3Mul2f(v, rdScale2f);
//     result = rdMat3Mul2f(&result, rdRotate2f);
//     result = rdMat3Mul2f(&result, rdTranslate2f);

//     return result;
// }
// float fShader(RdScreenPoint p, float color){
//     return color;
// }

int main(int argc, char* argv[]){
    vec3(float) a = {1, 2, 3};
    float m[4][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    auto b = mat4vec3(float)(&a, m);
    printf("%f %f %f %f\n", b.x, b.y, b.z, b.w);

    return 0;
}
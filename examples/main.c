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
    vec2(int) a = {1, 2};
    int m[2][2] = {
        {1, 2},
        {3, 4}
    };

    auto b = mat2vec2(int)(&a, m);

    printf("(%d, %d)\n", b.x, b.y);

    return 0;
}
#include <stdio.h>
#include "array.h"

int main(int argc, char* argv[]){
    std_array(float) nums = std_array_default(float, 5);

    foreach(nums){
        *it = (rand() % 100) / 10.0f;
        printf("%f\n", *it);
    }

    return 0;
}
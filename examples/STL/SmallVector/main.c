#include <stdio.h>
#include "small_vector.h"

int main(int argc, char* argv[]){
    std_small_vector(float) nums = std_small_vector_default(float);

    for(size_t i = 0; i < 10; i++)
        nums.push_back(&nums, (rand() % 100) / 10.0f);

    foreach(nums)
        printf("%f\n", *it);
    
    return 0;
}
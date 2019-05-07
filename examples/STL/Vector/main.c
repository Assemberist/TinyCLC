#include <stdio.h>
#include "vector.h"

int main(int argc, char* argv[]){
    std_vector(float) nums = std_vector_default(float);

    for(size_t i = 0; i < 10; i++)
        nums.push_back(&nums, (rand() % 100) / 10.0f);

    printf("size: %d capacity: %d\n", nums.size(&nums), nums.capacity(&nums));


    foreach(nums)
        printf("%f\n", *it);


    nums.destruct(&nums);
    return 0;
}
#include <stdio.h>
#include "algorithm.h"
#include "array.h"
#include "vector.h"
#include "small_vector.h"

ALGOS(std_array(float))
ALGOS(std_vector(float))
ALGOS(std_small_vector(float))

int main(int argc, char* argv[]){
    // init containers
    std_array(float) nums0 = std_array_default(float, 5);
    std_vector(float) nums1 = std_vector_default(float);
    std_small_vector(float) nums2 = std_small_vector_default(float);

    for(size_t i = 0; i < 5; i++){
        nums1.push_back(&nums1, (rand() % 100) / 10.0f);
        nums2.push_back(&nums2, (rand() % 100) / 10.0f);
    }

    foreach(nums0)
        *it = (rand() % 100) / 10.0f;

    // bubble sort algorithm
    std_bubble_sort(std_array(float))(std_begin(nums0), std_end(nums0));
    std_bubble_sort(std_vector(float))(std_begin(nums1), std_end(nums1));
    std_bubble_sort(std_small_vector(float))(std_begin(nums2), std_end(nums2));

    // output
    foreach(nums0) 
        printf("%f ", *it);
    puts("");

    foreach(nums1) 
        printf("%f ", *it);
    puts("");

    foreach(nums2) 
        printf("%f ", *it);
    puts("");

    // free
    nums1.destruct(&nums1);
    return 0;
}
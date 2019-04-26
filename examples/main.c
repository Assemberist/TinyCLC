#include <stdio.h>
#include "array.h"
#include "pair.h"

void bubble_sort(std_array(int)* arr){
    bool sorted = false;

    while(!sorted){
        sorted = true;
    
        foreach((*arr)){
            if(it != std_back(*arr)){
                auto next = it + 1;

                if(*next < *it){
                    std_swap(next, it);
                    sorted = false;
                }
            }
        }
    }
}

int main()
{
    std_array(int) arr;

    // init
    arr.size = 20;
    foreach(arr)
        *it = rand() % 10;
    
    // sort
    bubble_sort(&arr);

    // output
    foreach(arr)
        printf("%d\n", *it);

    return 0;
}
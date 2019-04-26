#include <stdio.h>
#include "array.h"


int main()
{
    std_array(float) arr = std_array_default(float, 5);
    
    foreach(arr){
        *it = rand() % 10;
        printf("%f\n", *it);
    }

    return 0;
}
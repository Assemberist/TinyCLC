#include <stdio.h>
#include "array.h"
#include "pair.h"

PAIRS(char, int)
ARRAYS(std_pair(char, int))

int main(){
    std_array(std_pair(char, int)) arr;
    arr.size = 2;

    foreach(arr){
        *it = std_make_pair(char, int)('1', 1);
        printf("(%c, %d)\n", it->first, it->second);
    }

    return 0;
}
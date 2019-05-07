#include <stdio.h>
#include "pair.h"

PAIRS(float, char)

int main(int argc, char* argv[]){
    std_pair(float, char) p = {-1.0f, 'a'};

    printf("%f %c\n", p.first, p.second);

    return 0;
}
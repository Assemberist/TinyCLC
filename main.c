#include <stdio.h>
#include "easycl.h"

int main(){
    _EclError err = {};
    err.code = -1;
    
    eclErrorCheck(&err, "Test");

    return 0;
}
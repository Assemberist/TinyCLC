#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <omp.h>

/////////////////////////////////////////////////////
//                     MACROS
/////////////////////////////////////////////////////
#define RD_NORMALIZED_FLOAT_MIN_ZERO(X) if(X < 0.0f) X = 0.0f;\
else if(X > 1.0f) X = 1.0f;

// #define RD_DEBUG
#define RD_SHOW_GRID
// #define RD_WHITE_BACK

/////////////////////////////////////////////////////
//                      MATH
/////////////////////////////////////////////////////

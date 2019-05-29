#!/bin/bash

gcc -E -std=c11 -I ../../ -I ../../vm256 main.c | grep -vE '^#' > main_e.c
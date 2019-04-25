#!/bin/bash

gcc -E -std=c11 -I ../ main.c | grep -vE '^#' > main_e.c
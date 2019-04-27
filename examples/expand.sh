#!/bin/bash

gcc -E -std=c11 -I ../ -I ../stl main.c | grep -vE '^#' > main_e.c
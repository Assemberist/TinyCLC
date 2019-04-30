#!/bin/bash

gcc -O2 -std=c11 -lm -fopenmp -I ../ -I ../stl main.c
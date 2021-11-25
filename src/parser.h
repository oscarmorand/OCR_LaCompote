#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>

void print_grid(int n, char** grid);

char** init_grid(size_t n);

void free_grid(size_t n, char** grid);

char** Load(size_t n, char *fileName);

void Save(char *fileName, char** grid);

#endif
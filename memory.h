#ifndef MEMORY_H
#define MEMORY_H
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

char mem[80];

bool read(const char * fileName);
void allocate(char process, int size, char algorithm);
int main();

#endif
#ifndef MEMORY_H
#define MEMORY_H
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MEM_SIZE 80
char mem[MEM_SIZE];

bool read(const char * fileName);
void showMem();
void compact();
bool firstFit(char process, int size);
bool worstFit(char process, int size);
bool bestFit(char proces, int size);
void deallocate(char process);
void allocate(char process, int size, char algorithm);
int main();

#endif
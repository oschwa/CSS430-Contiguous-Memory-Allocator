/**
 * Author: Oliver Schwab
 * Professor: Faisal Ahmed 
 * Class: CSS430 Spring 2024
 * Program Name: Contiguous Memory Allocator
 * Description: A simulator of how an operating system manages contiguous 
 * memory allocation. 
*/
#ifndef MEMORY_H
#define MEMORY_H
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MEM_SIZE 80
#define MAX_LINE 9
char mem[MEM_SIZE];

//  Read a .txt file containing a script for the program.
void read(const char * fileName);
//  Show the contents of memory.
void showMem();
//  Compact processes in memory to reduce fragmentation.
void compact();
//  Allocate via the first-fit algorithm.
bool firstFit(char process, int size);
//  Allocate via the worst-fit algorithm.
bool worstFit(char process, int size);
//  Allocate via the best-fit algorithm.
bool bestFit(char proces, int size);
//  Deallocate a process.
void deallocate(char process);
//  Allocate a process.
void allocate(char process, int size, char algorithm);
//  Driver.
int main();

#endif
#include "memory.h"

void showMem() {
    printf("\nMain Memory:\n");
    for (int i = 0; i < MEM_SIZE; i++) {
        if (mem[i] == '\0') {
            printf(".");
        } else { printf("%c", mem[i]); }
    }
    printf("\n\n");
}

bool firstFit(char process, int size) {
    //  find the first pocket that fits.
    int a = -1; int b = -1;
    for (int i = 0; i < MEM_SIZE; i++) {
        if (mem[i] == '\0' && a == -1) { 
            a = i; b = i;
        } else if (mem[i] == '\0') {   
            ++b;
        } else {
            if (b - a >= size) {
                break;
            } else { a = -1; b = -1; }
        }
    }
    //  determine if there is space.
    if (b - a < (size - 1)) { return false; }
    //  allocate to available memory.
    b = a + (size - 1);
    for (int i = a; i <= b; i++) {
        mem[i] = process;
    }
    return true;
}

bool worstFit(char process, int size) {
    //  find the worst-size pocket.
    int wA = -1; int wB = -1;
    int a = -1; int b = -1;
    for (int i = 0; i < MEM_SIZE; i++) {
        if (mem[i] == '\0' && a == -1) { 
            a = i; b = i;
        } else if (mem[i] == '\0') {   
            ++b;
        } else {
            if (b - a > wB - wA) {
                wA = a;
                wB = b;
            } else { a = -1; b = -1; }
        }
    }
    if (wA == -1 && wB == -1) {
        wA = a;
        wB = b;
    }
    //  determine if there is space.
    if (wB - wA < (size - 1)) { return false; }
    //  allocate to available memory.
    wB = wA + (size - 1);
    for (int i = wA; i <= wB; i++) {
        mem[i] = process;
    }
    return true;
}

void deallocate(char process) {
    bool exists = false;
    for (int i = 0; i < MEM_SIZE; i++) {
        if (mem[i] == process) {
            exists = true;
            mem[i] = '\0';
        }
    }
    if (!exists) {
        printf("    ERROR: Process %c does not exist in memory.\n", process);
    }
}

void allocate(char process, int size, char algorithm) {
    if (algorithm == 'F') { 
        if (!firstFit(process, size)) {
            printf("    ERROR: Memory does not have sufficient space\n     - Please deallocate a process to allocate %c.\n", process);
        }
    } else if (algorithm == 'W') {
        if (!worstFit(process, size)) {
            printf("    ERROR: Memory does not have sufficient space\n     - Please deallocate a process to allocate %c.\n", process);
        }
    }
}

bool read(const char * fileName) {
    //  TODO: Implement later.
    return false;
}

int main() {
    printf("-----Welcome to the Contiguous Memory Allocator-----\n\n");
    char line[50];
    char cmd;

    while (true) {
        printf("Enter a command:\n     ");
        scanf(" %c", &cmd);
        if (cmd == 'A') {
            char process, algorithm;
            int size;
            scanf(" %c %d %c", &process, &size, &algorithm);
            allocate(process, size, algorithm);
        } else if (cmd == 'F') {
            char process;
            scanf(" %c", &process);
            deallocate(process);
        } else if (cmd == 'S') {
            showMem();
        } else if (cmd == 'R') {
            scanf(" %s", line);
            read(line);
        } else if (cmd == 'E') {
            printf("Exiting the Contiguous Memory Allocator...\n");
            return 0;
        } else {
            printf("    ERROR: Invalid input - try again.\n");
            fflush(stdout);
        }
    }
}
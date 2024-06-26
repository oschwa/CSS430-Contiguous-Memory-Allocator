/**
 * Author: Oliver Schwab
 * Professor: Faisal Ahmed
 * Class: CSS430 Spring 2024
 * Description: Implementation file for 
 * "memory.h" interface.
*/
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

void compact() {
    for (int i = 1; i < MEM_SIZE; i++) {
        if (mem[i] != '\0' && mem[i - 1] == '\0') {
            for (int j = i - 1; j >= 0; j--) {
                if (mem[j] != '\0') {
                    mem[j + 1] = mem[i];
                    mem[i] = '\0';
                    break;
                }
            }
        }
    }
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
            //  if the current window is bigger
            //  than the known biggest, then 
            //  update. 
            if (b - a > wB - wA) {
                wA = a;
                wB = b;
            } else { a = -1; b = -1; }
        }
    }

    if ((wA == -1 && wB == -1) || b - a > wB - wA) {
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

bool bestFit(char process, int size) {
    int bA = -1; int bB = -1;
    int a = -1; int b = -1;
    for (int i = 0; i < MEM_SIZE; i++) {
        if (mem[i] == '\0' && a == -1) { 
            a = i; b = i;
        } else if (mem[i] == '\0') {   
            ++b;
        } else {
            //  if the current window is smaller than the 
            //  current minimum window, yet big enough to
            //  fit the process, then assign new 
            //  values.
            if (b - a < bB - bA && (b - a) >= size) {
                bA = a;
                bB = b;
            } else { a = -1; b = -1; }
        }
    }
    if (bA == -1 && bB == -1) {
        bA = a;
        bB = b;
    }
    //  determine if there is space.
    if (bB - bA < (size - 1)) { return false; }
    //  allocate to available memory.
    bB = bA + (size - 1);
    for (int i = bA; i <= bB; i++) {
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
    } else if (algorithm == 'B') {
        if (!bestFit(process, size)) {
            printf("    ERROR: Memory does not have sufficient space\n     - Please deallocate a process to allocate %c.\n", process);
        }
    } else {
        printf("    ERROR: Algorithm %c is not an option for memory allocation - Please choose from the following:\n", algorithm);
        printf("    F -> First-Fit\n    B -> Best-Fit\n    W -> Worst-Fit\n");
    }
}

void read(const char * fileName) {
    FILE *f = fopen(fileName, "r");
    if (!f) {
        printf("    ERROR: File failed to open successfully.\n");
        fclose(f);
        return;
    }
    char line[MAX_LINE];
    while(fgets(line, MAX_LINE, f)) {
        char cmd;
        cmd = line[0];
        if (cmd == 'A') {
            int i = 1;
            while (line[i] == ' ') {++i;}
            char process = line[i++];

            while (line[i] == ' ') {++i;}
            char n[3] = {'\0'};
            int j = 0;
            while (line[i] != ' ') {
                n[j++] = line[i++];
            }
            int size = atoi(n);
            while (line[i] == ' ') {++i;}
            char algorithm = line[i];

            allocate(process, size, algorithm);
        } else if (cmd == 'F') {
            int i = 1;
            while (line[i] == ' ') {++i;}
            char process = line[i];
            deallocate(process);
        } else if (cmd == 'C') {
            compact();
        } else if (cmd == 'S') {
            showMem();
        } else if (cmd == 'E') {
            return;
        } 
    }   
    fclose(f);
}

int main() {
    printf("-----Welcome to the Contiguous Memory Allocator-----\n\n");
    char line[MAX_LINE];
    char cmd;

    while (true) {
        printf("Enter a command:\n     ");
        scanf(" %c", &cmd);
        if (cmd == 'A') {
            char process, algorithm;
            int size;
            scanf(" %c %d %c", &process, &size, &algorithm);
            allocate(process, size, algorithm);
        } else if (cmd == 'C') {
            compact();
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
            exit(0);
        } else {
            printf("    ERROR: Invalid input - try again.\n");
            fflush(stdout);
        }
    }
}
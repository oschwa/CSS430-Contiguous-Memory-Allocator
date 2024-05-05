#include "memory.h"

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
    
        switch (cmd) 
        {
            case 'A':
                break;
            case 'R': 
                scanf(" %s", line);
                read(line);
                break;
            case 'E': 
                printf("Exiting the Contiguous Memory Allocator...\n");
                return 0;
            default: break;
        }
    }
}
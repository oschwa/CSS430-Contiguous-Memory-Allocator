# CSS430-Contiguous-Memory-Allocator
Welcome to the Contiguous Memory Allocator!

This project is an interactive simulation of how contiguous memory works with Operating Systems.

There are three kinds of memory allocation that this project implements:
- Best-Fit
- Worst-Fit
- First-Fit

On top of this, compaction is also supported for simulated memory.

## Build Instructions
1. Clone this repository on your local machine.
2. Run one of the following compilation commands in your terminal.
- For GCC/GNU -> gcc -o memory-allocator.out memory.c
- For macOS -> clang -o memory-allocator.out memory.c

3. You will be presented with this screen:

<img width="387" alt="Screenshot 2024-05-07 at 2 10 25 PM" src="https://github.com/oschwa/CSS430-Contiguous-Memory-Allocator/assets/114828394/ff5738bc-ca52-4d99-8ca1-dcc011711d0f">

Commands follow the given format: [Command Letter] [args..]

Your available command letters are: 
- A -> allocate a process to memory, with format "A [process letter name] [byte size of process] [algorithm for allocation]"
- F -> deallocate a process from memory, with format "F [process letter name]
- C -> Compact memory
- S -> Show the current state of the memory.
- R -> Read a .txt file of commands for simulated memory, with given format "R [file name].txt" (A text file is provided for use).

Your available options are:
- W -> Worst-Fit
- B -> Best-Fit
- F -> First-Fit

## Constraints 
1. Names of process must be a single character. For example, if I were to allocate a new process, it would have to be akin to the following:

`A G 10 F` 

(With 'G' being the process name, '10' being the size of the process, and 'F' being the First-Fit algorithm.)

2. The size of the process cannot exceed 80 (representative of 80 bytes).
3. Text files of commands must follow the exact same format as the provided script. 


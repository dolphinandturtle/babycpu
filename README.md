# Abstract
This is a *toy model* of a CPU based after the [Von Neumann Architecture](https://en.wikipedia.org/wiki/Von_Neumann_architecture),
its purpose is purely didactic. A **program** is written as an array of 16-bit integers inside of a **memory** buffer that is
being iterated over sequentially following a CPU **counter**, each integer is then getting loaded into the CPU **instruction**
buffer that proceeds to apply one or more of the following:
1. Read operation (move data from the memory onto the CPU: *LOAD*).
2. Write operation (move data from the CPU to the memory: *STORE*).
3. Arithmetic operation (perform arithmetic onto data loaded onto the CPU: *INCREMENT*, *ADD* and *SUB*).
4. Control flow operation (modify the CPU counter: *JUMP* and *JUMP_IF_GREATER*).

## Features
1. The CPU processes in 16-bit instructions.
2. The CPU has four 8-bit registers, arithmetic on the 0-255 range.
3. The CPU has a 4-bit address counter, has access to 16 memory slots.
4. At each CPU cycle the memory and CPU counter is printed onto the screen.

## Instruction format
|empty|operation|register-0|register-1|address|
|-----|---------|----------|----------|-------|
| 0000|     0000|        00|        00|   0000|

# Installation (Linux)
`gcc -o main load_add_store.c babycpu.c`

# Abstract
This is a *toy model* of a CPU based after the [Von Neumann Architecture](https://en.wikipedia.org/wiki/Von_Neumann_architecture),
its purpose is purely didactic. A **program** is written as an array of 16-bit integers inside of a **memory** buffer that is
being iterated over sequentially following a CPU **counter**, each integer is then getting loaded into the CPU **instruction**
buffer that proceeds to apply one or more of the following:
1. Read operation (move data from the memory onto the CPU: *LOAD*).
2. Write operation (move data from the CPU to the memory: *STORE*).
3. Arithmetic operation (perform arithmetic onto data loaded onto the CPU: *INCREMENT*, *ADD* and *SUB*).
4. Control flow operation (modify the CPU counter: *JUMP* and *JUMP_IF_GREATER*).

# Features
1. The CPU processes in 16-bit instructions.
2. The CPU has four 8-bit registers, arithmetic on the 0-255 range.
3. The CPU has a 4-bit address counter, has access to 16 memory slots.
4. At each CPU cycle the memory and CPU counter is printed onto the screen.

# Instructions

## LOAD
### LOAD (Address)
Load bytes of memory via an address onto a specific register.

|operation|register-0|register-s|    address|
|---------|----------|----------|-----------|
|    000 0|        XX|        00|   XXXXXXXX|

### LOAD (Immediate)
Load fixed bytes onto specific register.

|operation|register-0|register-s|      value|
|---------|----------|----------|-----------|
|    000 0|        XX|        01|   XXXXXXXX|

### LOAD (Register)
Load from first and second register onto any other register.

|operation|register-0|register-s|    address|
|---------|----------|----------|-----------|
|    000 1|        XX|  00 or 01|   ????????|

### LOAD (Index Register)
Load from memory via address on third and fourth register onto any other register.

|operation|register-0|register-s|    address|
|---------|----------|----------|-----------|
|    000 1|        XX|  10 or 11|   ????????|

## STORE
### STORE (address)
Store register bytes onto memory via an address.

|operation|register-0|register-s|    address|
|---------|----------|----------|-----------|
|    001 0|        XX|        00|   XXXXXXXX|

### STORE (immeddiate)
Store fixed bytes onto memory via an address.

|operation|register-0|register-s|      value|
|---------|----------|----------|-----------|
|    001 0|        XX|        01|   XXXXXXXX|

### STORE (register)
Store any register bytes onto first and second register.

|operation|register-0|register-s|    address|
|---------|----------|----------|-----------|
|    001 1|        XX|  00 or 01|   ????????|

### STORE (index register)
Store onto memory via address on third and fourth register.

|operation|register-0|register-s|    address|
|---------|----------|----------|-----------|
|    001 1|        XX|  10 or 11|   ????????|

## Addition
### Addition (register)
|operation|register-0|register-s|    address|
|---------|----------|----------|-----------|
|    010 0|        ??|        ??|   ????????|

### Addition (immediate)
|operation|register-0|register-s|    address|
|---------|----------|----------|-----------|
|    010 1|        ??|        ??|   XXXXXXXX|

## Subtraction
### Subtraction (register)
|operation|register-0|register-s|    address|
|---------|----------|----------|-----------|
|    011 0|        ??|        ??|   ????????|

### Subtraction (immediate)
|operation|register-0|register-s|    address|
|---------|----------|----------|-----------|
|    011 1|        ??|        ??|   XXXXXXXX|

## Multiplication
### Multiplication (register)
|operation|register-0|register-s|    address|
|---------|----------|----------|-----------|
|    100 0|        ??|        ??|   ????????|

### Multiplication (immediate)
|operation|register-0|register-s|    address|
|---------|----------|----------|-----------|
|    100 1|        ??|        ??|   XXXXXXXX|

## Jump
### Jump (immediate)
|operation|register-0|register-s|    address|
|---------|----------|----------|-----------|
|    101 0|        ??|        ??|   XXXXXXXX|

### Jump (index register)
|operation|register-0|register-s|    address|
|---------|----------|----------|-----------|
|    101 1|        XX|        ??|   ????????|

# Installation (Linux)
`make`

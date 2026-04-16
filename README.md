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
## LOAD (address)
Load bytes of memory via an address onto a specific register.
|operation|register-0|register-s|    address|
|---------|----------|----------|-----------|
|     0000|        XX|        00|   XXXXXXXX|

## LOAD (immediate)
Load fixed bytes onto specific register.
|operation|register-0|register-s|      value|
|---------|----------|----------|-----------|
|     0000|        XX|        01|   XXXXXXXX|

## LOAD (index register)
Load from memory via address on third and fourth register onto any other register.
|operation|register-0|register-s|    address|
|---------|----------|----------|-----------|
|     0000|        XX|        10|   ????????|

## LOAD (local register)
Load the first register onto the third register 
(1->3).
|operation|register-0|register-s|    address|
|---------|----------|----------|-----------|
|     0000|        00|        11|   ????????|

Load the second register onto the first register 
(2->1).
|operation|register-0|register-s|    address|
|---------|----------|----------|-----------|
|     0000|        01|        11|   ????????|

Load the third register onto the second register 
(3->2).
|operation|register-0|register-s|    address|
|---------|----------|----------|-----------|
|     0000|        10|        11|   ????????|

Load the fourth register onto the third register 
(4->3).
|operation|register-0|register-s|    address|
|---------|----------|----------|-----------|
|     0000|        11|        11|   ????????|

## STORE (address)
Store register bytes onto memory via an address.
|operation|register-0|register-s|    address|
|---------|----------|----------|-----------|
|     0001|        XX|        00|   XXXXXXXX|

## STORE (immediate)
Store fixed bytes onto memory via an address.
|operation|register-0|register-s|      value|
|---------|----------|----------|-----------|
|     0001|        XX|        01|   XXXXXXXX|

## STORE (index register)
Store onto memory via address on third and fourth 
register.
|operation|register-0|register-s|    address|
|---------|----------|----------|-----------|
|     0001|        XX|  10 or 11|   ????????|

## Addition (register)
Add second register to first register.
|operation|register-0|register-s|    address|
|---------|----------|----------|-----------|
|     0010|        XX|        XX|   ????????|

## Subtraction (register)
Subtract second register to first register.
|operation|register-0|register-s|    address|
|---------|----------|----------|-----------|
|     0011|        XX|        XX|   ????????|

## Multiplication (register)
Multiply second register to first register.
|operation|register-0|register-s|    address|
|---------|----------|----------|-----------|
|     0100|        XX|        XX|   ????????|

## Jump (immediate)
Program counter is changed to the given address.
|operation|register-0|register-s|    address|
|---------|----------|----------|-----------|
|     0101|        ??|        ??|   XXXXXXXX|

## Conditional Jump (positive register)
Program counter is changed to the given address if 
the first register is greater than the second 
register.
|operation|register-0|register-s|    address|
|---------|----------|----------|-----------|
|     0110|        XX|        XX|   XXXXXXXX|

# Installation (Linux)
`make`

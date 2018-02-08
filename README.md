# CSCI431
## Summary
This repository includes all necessary source code, screenshots, and documentation for the CSCI-431 program required for the Senior Portfolio for student 163119.

## What the program does
This program utilizes threading to efficiently count the number of primes from 2 to N

## How to compile it
*NOTE:* This program is **not** an application in the general sense.  It is a software representation of a hardware component.  The execute.v is the primary software component and the executeTB.v is a test program to demonstrate it's use.

*NOTE:* These instructions assume standard Linux OS, terminal, Icarus Verilog, and GTKWave are installed.
1. Open Terminal
1. gcc -o run {INSTALL DIR}/src/lab02-2.c
1. ./run {number of threads to use} {N}

# Memory Allocator Simulation in C

## Overview

This repository contains a simple implementation of a memory allocator in C, providing a basic version of `malloc()` and `free()` functions. This project was developed as part of a university assignment, inspired by the logic outlined in an online article ([link](https://everything1know.wordpress.com/2016/02/05/mymalloc-custom-memory-allocation-library/)).

## Features

- **Memory Allocation**: The `MyMalloc()` function allocates a block of memory of the specified size.
- **Memory Deallocation**: The `MyFree()` function frees a previously allocated block of memory.
- **Memory Block Information**: The `printMemoryBlocks()` function prints information about the current state of memory blocks, including their status (allocated or free), size, and locations.

## Usage


## Notes

- The `initialize()` function initializes the memory pool if it hasn't been done already.
- The memory pool is represented by a character array (`mem_pool`), with each character representing one byte.
- The memory block structure (`struct head`) contains information about the block's status (free or allocated) and size.
- The logic behind splitting and merging memory blocks is implemented to optimize memory usage.

Feel free to explore the code and experiment with different allocations and deallocations.

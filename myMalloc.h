#ifndef MYMALLOC_H
#define MYMALLOC_H

#define MEM_SIZE 25000 - 1
#define HEAD_SIZE 8 //sizeof(struct head)

void printMemoryBlocks();
void MyFree(void *ptr);
void *MyMalloc(int size);
void initialize();

#endif
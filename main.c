#include <stdio.h>
#include "myMalloc.h"

int main(){

    char *test1 = MyMalloc(20000);
    printf("test1: %p\n", test1);
    // printMemoryBlocks();

    char *test2 = MyMalloc(4000);
    printf("test2: %p\n", test2);
    // printMemoryBlocks();

    char *test3 = MyMalloc(900);
    printf("test3: %p\n", test3);
    // printMemoryBlocks();

    char *test4 = MyMalloc(58);
    printf("test4: %p\n", test4);
    printMemoryBlocks();

    // MyFree(test1);
    // printMemoryBlocks();

    MyFree(test2);
    printMemoryBlocks();
    
    // MyFree(test4);
    // printMemoryBlocks();

    // MyFree(test3);
    // printMemoryBlocks();

}
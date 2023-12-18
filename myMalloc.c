#include <stdio.h>
#include "myMalloc.h"


// char array to b used as memory pool, here char array is used because char is one byte
//  so individual char can represent individual bytes 
char mem_pool[MEM_SIZE] = {'\0'};

// structure of header of individual memory block
struct head
{
    char flag;
    int size;
};

void initialize()
{
    // check if initilaized and if not then initialize else return
    if(!mem_pool[0]){

        printf("Initialize was called\n");
        // giving all values in the memory pool char '0' value
        int i;
        for (i = 0; i < MEM_SIZE; i++){
            mem_pool[i] = '0';
        }
        // initalizing first char of memory to char '1'
        mem_pool[1] = '1';

        // creating first header for storing data about first free memory block
        struct head *first_header = (void*)&mem_pool[1];
        first_header->flag = 'f';
        first_header->size = MEM_SIZE - HEAD_SIZE;
        
    }

}

void* MyMalloc(int size)
{
    // initializing if not initialized
    initialize();

    // pointer for traversing memory
    struct head *block = (void*)&mem_pool[1];

    // while condition checks if memory location of pointer is out of memory
    while((void*)block < (void*)&mem_pool[MEM_SIZE]){   
        // check if block is free or allocated and space is enough
        if(block->flag == 'f' && block->size >= size){
            block->flag = 'a';
            //check if enough space have to split to two blocks
            if(block->size > size + HEAD_SIZE){
                //there is enough space to break the block into two and create another block
                // create another header for remaing free space
                struct head *tmp = (void*)block + HEAD_SIZE + size;
                tmp->flag = 'f';
                tmp->size = block->size - HEAD_SIZE - size;
                block->size = size;
            }
            return (void*)block + HEAD_SIZE;
            
        }
        else{
            //incrementing the pointer in the memory pool
            block = (void*)block + HEAD_SIZE + block->size;
        }
    }
    printf("No Memory!!\n");
    return NULL;

}

void MyFree(void *ptr)
{
    // creating two pointers for keeping track of present memory block and previous memory block
    struct head *block = (void*)&mem_pool[1];
    struct head *prev_block = block;

    // while condition checks if memory location of pointer is out of memory
    while((void*)block < (void*)&mem_pool[MEM_SIZE]){
        if((void*)block + HEAD_SIZE == ptr){
            //we have found the address

            //set block as free
            block->flag = 'f';

            //previous pointer is also free join both
            if(prev_block->flag == 'f' && block != prev_block){
                prev_block->size += block->size + HEAD_SIZE;
                
                // set pointer to previous block
                block = prev_block;
            }

            //next block is also free must join
            struct head *nextblock = (void*)block + HEAD_SIZE + block->size;
            if(nextblock->flag == 'f'){
                // merge next block into present block by increasing size
                block->size += nextblock->size + HEAD_SIZE;
            }
            return;
        }
        else{
            //increment pointers
            prev_block = block;
            block = (void*)block + HEAD_SIZE + block->size;
        }
    }
    printf("Address pointer to be freed not found!!\n");

}

void printMemoryBlocks(){
     printf("----------------------------------------------------------------\n\n");
    struct head *block = (void*)&mem_pool[1];
    while((void*)block < (void*)&mem_pool[MEM_SIZE]){
        if (block->flag == 'f')
        {
        	printf("STATUS         ---------------------> FREE\n");
        }
        else if (block->flag == 'a')
        {
        	printf("STATUS         ---------------------> ALLOCATED\n");
        }
        else
        {
        	printf("STATUS         ---------------------> ERROR!!!!\n");
            break;
        }
        printf("SIZE           ---------------------> %d\n",block->size);
        printf("START LOCATION ---------------------> %p\n",(void*)block + HEAD_SIZE);
        printf("END LOCATION   ---------------------> %p\n",(void*)block + HEAD_SIZE + block->size - 1);
        printf("START LOCATION (in mem_pool array)--> %d\n",(int)((void*)block + HEAD_SIZE - (void*)mem_pool));
        printf("END LOCATION   (in mem_pool array)--> %d\n",(int)((void*)block + HEAD_SIZE + block->size - 1 - (void*)mem_pool));

        printf("\n");

        block = (void*)block + HEAD_SIZE + block->size;
        
         
    }
    printf("----------------------------------------------------------------\n");
}




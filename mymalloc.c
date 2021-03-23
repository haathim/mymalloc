#include <stdio.h>
#define MEM_SIZE 25000 - 1
#define HEAD_SIZE 8 //sizeof(struct head)

char mem_pool[MEM_SIZE] = {'\0'};

struct head
{
    char flag;
    int size;
};

void initialize()
{
    if(!mem_pool[0]){

        printf("Initialize was called\n");
        int i;
        for (i = 0; i < MEM_SIZE; i++){
            mem_pool[i] = '0';
        }
        mem_pool[0] = '1';

        struct head *first_header = (void*)&mem_pool[1];
        first_header->flag = 'f';
        first_header->size = MEM_SIZE - HEAD_SIZE;
        
    }

}

void* MyMalloc(int size)
{
    initialize();

    struct head *block = (void*)&mem_pool[1];

    while((void*)block < (void*)&mem_pool[MEM_SIZE]){   
        if(block->flag == 'f' && block->size >= size){
            block->flag = 'a';
            if(block->size > size + HEAD_SIZE){

                struct head *tmp = (void*)block + HEAD_SIZE + size;
                tmp->flag = 'f';
                tmp->size = block->size - HEAD_SIZE - size;
                block->size = size;
            }
            printf("DONE\n");
            return (void*)block + HEAD_SIZE;
            
        }
        else{
            block = (void*)block + HEAD_SIZE + block->size;
        }
    }
    printf("No Memory!!\n");
    return NULL;

}

void MyFree(void *ptr)
{
    struct head *block = (void*)&mem_pool[1];
    struct head *prev_block = block;

    while((void*)block < (void*)&mem_pool[MEM_SIZE]){
        if((void*)block + HEAD_SIZE == ptr){

            block->flag = 'f';

            if(prev_block->flag == 'f' && block != prev_block){
                prev_block->size += block->size + HEAD_SIZE;
                
                block = prev_block;
            }

            struct head *nextblock = (void*)block + HEAD_SIZE + block->size;
            if(nextblock->flag == 'f'){
                block->size += nextblock->size + HEAD_SIZE;
            }
            printf("FREED\n");
            return;
        }
        else{
            prev_block = block;
            block = (void*)block + HEAD_SIZE + block->size;
        }
    }
    printf("Address pointer to be freed not found!!\n");

}

int main(){

    char *test1 = MyMalloc(50);

    int *test2 = MyMalloc(10);

    char *test3 = MyMalloc(20);

    MyFree(test1);

    



}




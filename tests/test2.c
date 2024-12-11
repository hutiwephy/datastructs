#include <stdio.h>
#include <stdlib.h>
#include <ctools/array.h>


#define LENGTH 10

int main(int argc, char* argv[]){
    int** array = NULL;

    for(int i=0; i<LENGTH; i++){
        int* item = malloc(sizeof(int));
        *item = 5;
        if(array_push_back(&array, item) == 0){
            printf("ERROR: out of memory!");
            getchar();
            return -1;
        }
    }

    *(array[LENGTH-1]) = 9;

    int* item = malloc(sizeof(int));
    *item = 0;

    array_insert(&array, LENGTH, item);
    item = malloc(sizeof(int));
    *item = 0;
    array_insert(&array, 0, item);
    item = malloc(sizeof(int));
    *item = 0;
    array_insert(&array, 4, item); // 5th item should be 0


    for(int i=0; array[i] != NULL; i++){
        printf("%d, ", *(array[i]));
    }

    printf("\nlength: %d\n", array_length(&array));

    item = array_remove(&array, 4);
    printf("%d, \n", *item);

    for(int i=0; i<LENGTH+4; i++){
        item = array_pop_back(&array);
        if(item == NULL){
            printf("NULL, ");
        }else{
            printf("%d, ", *item);
            free(item);
        }
    }


    getchar();
    return 0;
}

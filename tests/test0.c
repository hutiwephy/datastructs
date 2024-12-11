#include <stdio.h>
#include <stdlib.h>
#include <ctools/array.h>

int main(int argc, char* argv[]){
    void** arr = malloc(15*sizeof(void*));
    arr[14] = NULL;
    
    printf("length: %d", array_length(&arr));

    getchar();
    return 0;
}

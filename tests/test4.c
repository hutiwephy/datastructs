#include <stdio.h>
#include <stdlib.h>
#include <ctools/array.h>


void printnums(int* nums, int len){
    for(int i=0; i<len; i++){
        printf("%d, ", nums[i]);
    }
    printf("\n");
}

int main(int argc, char* argv[]){
    
    int* nums = malloc(5);
    for(int i=0; i<5; i++){
        nums[i] = 5;
    }

    printnums(nums, 5);

    int num = 1;
    memins((void**)&nums, sizeof(int), 5, 2, &num);

    printnums(nums, 6);

    memrem((void**)&nums, sizeof(int), 6, 2);

    
    printnums(nums, 5);

    getchar();
    return 0;
}

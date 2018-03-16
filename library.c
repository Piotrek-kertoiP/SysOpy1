#include "library.h"
#include <malloc.h>
#include <string.h>
#include <stdlib.h>


char staticAllocatedArray[1000][200];

int sumOfAsciiCodes(char* block){
    int sum = 0;
    int i;
    for (i = 0; i < strlen(block); i++) {
        sum += (int) block[i];
    }
    return sum;
}

BlockArray *initArray(int array_size, int block_size, int isDynamic) {
    BlockArray *array = (BlockArray *) calloc(1, sizeof(BlockArray));
    if (isDynamic) {
        char **stringArray = (char **) calloc((size_t) array_size, sizeof(char *));
        array->array = stringArray;
        array->size_max = array_size;
        array->size_block = block_size;
        array->isDynamicAllocated = 1;
        return array;
    }
    array->array =(char **) staticAllocatedArray;
    array->size_max = array_size;
    array->size_block = block_size;
    array->isDynamicAllocated = 0;
    return  array;
}

void cleanStaticArray(BlockArray *staticArray){
    int i;
    for (i = 0; i < staticArray->size_max; ++i) {
            staticArray->array[i] = "";
    }
}

void deleteArray(BlockArray* blockArray){
    if (blockArray->isDynamicAllocated) {
        int i;
        for (i = 0; i < blockArray->size_max; ++i) {
            free(blockArray->array[i]);
        }
        free(blockArray->array);
        free(blockArray);
        return;
    } else{
        cleanStaticArray(blockArray);
    }
}

void removeBlock(BlockArray* blockArray, int index){
    if (blockArray->isDynamicAllocated) {
        free(blockArray->array[index]);
        blockArray->array[index] = NULL;
        return;
    }
        blockArray->array[index] = "";
}

void addBlock(BlockArray* blockArray, int index, char* block){
    if (index >= blockArray->size_max){
        printf("Index is too big\n");
        return;
    }else if(strlen(block)>=blockArray->size_block) {
        printf("String is too long for this array.\n");
        return;
    }
    else {
        if (blockArray->isDynamicAllocated) {
            if (blockArray->array[index] != NULL) removeBlock(blockArray, index);
            blockArray->array[index] = (char *) calloc((size_t) blockArray->size_block, sizeof(char));
            strcpy(blockArray->array[index], block);
            return;
        } else
            blockArray->array[index] = block;
    }
}



char* findClosestByAscii(BlockArray* blockArray, int index){
    char* tmpClosestBlock;
    int lowestDifference = 32767;
    int sum = sumOfAsciiCodes(blockArray->array[index]);
    int tmpSum;

    int i;
    for (i = 0; i < blockArray->size_max; ++i) {
        if (i != index){
            tmpSum = sumOfAsciiCodes(blockArray->array[i]);
            if ((abs(sum - tmpSum) < lowestDifference ) && tmpSum!=0){
                lowestDifference = abs(sum - tmpSum);
                tmpClosestBlock = blockArray->array[i];
            }
        }
    }
    return tmpClosestBlock;
}


char* generateRandomString(int maxSize){
    if (maxSize < 1) return NULL;
    char *base = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    size_t baseLength = strlen(base);
    char *newString = (char *) malloc((maxSize) * sizeof(char));
    int newStringLength = maxSize - (rand() % maxSize);

    int i;
    for (i = 0; i < newStringLength; ++i) {
        newString[i] = base[rand()%baseLength];
    }
    for (i = newStringLength; i < maxSize + 1; i++){
        newString[i] = '\0';
    }
    return newString;
}

void fillArray(BlockArray *blockArray){
    int i;
    for (i = 0; i < blockArray->size_max; ++i) {
        char* randomString = generateRandomString(blockArray->size_block);
        addBlock(blockArray, i, randomString);
    }
}

void addSpecificNumberOfBlocks(BlockArray *blockArray, int blocksNumber, int startIndex){
    int i;
    for (i = 0; i < blocksNumber; ++i) {
        char *block = generateRandomString(blockArray->size_block);
        addBlock(blockArray, startIndex, block);
        startIndex++;
    }
}

void removeSpecificNumberOfBlocks(BlockArray *blockArray, int blocksNumber, int startIndex){
    int i;
    for (i = 0; i < blocksNumber; ++i) {
        removeBlock(blockArray, startIndex);
        startIndex++;
    }
}

void deleteThenAdd(BlockArray *blockArray, int blocksNumber){
    removeSpecificNumberOfBlocks(blockArray, blocksNumber, 0);
    addSpecificNumberOfBlocks(blockArray, blocksNumber, 0);
}

void alternatelyDeleteAndAdd(BlockArray *blockArray, int blocksNumber){
    int i;
    for(i=0; i<blocksNumber; i++){
        removeBlock(blockArray, 0);
        addBlock(blockArray, 0, generateRandomString(blockArray->size_block) );
    }
    for (i = 0; i < blocksNumber; ++i) {
        removeBlock(blockArray, i);
        addBlock(blockArray, i, generateRandomString(blockArray->size_block));
    }
}

//double calculateTime(clock_t start, clock_t end){
//    return (double)( end -  start)  / sysconf(_SC_CLK_TCK);
//}


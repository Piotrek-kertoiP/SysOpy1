#include <stdio.h>
#include "library.h"
#include <sys/times.h>
#include <math.h>

void startMeassuringTime(struct rusage usage, struct timeval start_sys, struct timeval start_u, struct timeval start_real){
    getrusage(RUSAGE_SELF, &usage);
    start_sys = usage.ru_stime;
    start_u = usage.ru_utime;
    gettimeofday(&start_real,NULL);
}

void endMeassuringTime(struct rusage usage, struct timeval end_sys, struct timeval end_u, struct timeval end_real){
    getrusage(RUSAGE_SELF, &usage);
    end_sys = usage.ru_stime;
    end_u = usage.ru_utime;
    gettimeofday(&end_real,NULL);
}

void print_time(struct timeval start_sys,struct timeval end_sys, struct timeval start_u, struct timeval end_u,struct timeval start_real,struct timeval end_real){
    printf("Real time: %f\n", (float)(end_real.tv_sec-start_real.tv_sec)+(float)(end_real.tv_usec-start_real.tv_usec)*pow(10,-6));
    printf("System time: %f\n", (float)(end_sys.tv_sec-start_sys.tv_sec)+(float)(end_sys.tv_usec-start_sys.tv_usec)*pow(10,-6));
    printf("User time: %f\n", (float)(end_u.tv_sec-start_u.tv_sec)+(float)(end_u.tv_usec-start_u.tv_usec)*pow(10,-6));
}


//przeka¿ liczbê elementów tablicy, rozmiar bloku, sposób alokacji  pamiêci oraz spis wykonywanych operacji
int main(int arraySize, int blockSize, int isDynamic, char* operation){

    //stworzenie tablicy z zadan¹ liczb¹ bloków o zdanym rozmiarze i przy pomocy wybranej funkcji alokuj¹cej,
    BlockArray *array= initArray(arraySize, blockSize, isDynamic);
    fillArray(array);

    struct rusage usage;
    struct timeval start_sys, end_sys, start_u, end_u, start_real, end_real;

    //wyszukanie najbardziej podobnego elementu z punktu widzenia sumy znaków do elementu zadanego jako argument
    if( operation == "find")
    {
        startMeassuringTime(usage, start_sys, start_u, start_real);
        char* closestBlock = findClosestByAscii(array, arraySize/2);
        endMeassuringTime(usage, end_sys, end_u, end_real);
    }
    else
    {
    //usuniêcie kolejno zadanej liczby bloków a nastêpnie dodanie  na ich miejsce nowych bloków
        if( operation == "altDelAdd")
        {
            startMeassuringTime(usage, start_sys, start_u, start_real);
            alternatelyDeleteAndAdd(array, arraySize/2);
            endMeassuringTime(usage, end_sys, end_u, end_real);
        }
    }
    else
    {
        //na przemian usuniêcie i dodanie zadanej liczby bloków
        if( operation == "delAdd")
        {
            startMeassuringTime(usage, start_sys, start_u, start_real);
            deleteThenAdd(array, arraySize/2);
            endMeassuringTime(usage, end_sys, end_u, end_real);
        }
    }

    print_time(start_sys, end_sys, start_u, end_u, start_real, end_real);
    return 0;
}

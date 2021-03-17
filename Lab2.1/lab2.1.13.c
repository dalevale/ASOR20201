#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<sys/time.h>
#define LOOP 1000000
extern int errno;

int main(){

    struct timeval tv, tvElapsed;
    unsigned int startTime, endTime, elapsedTime;
    int i = 0;

    if(gettimeofday(&tv, NULL)){
        fprintf(stderr, "Error %d: %s\n", errno, strerror(errno));
        return 0;
    } 

    for(i = 0; i < LOOP; i++)
        printf("Number is set to: %d\n", i);
    
    if(gettimeofday(&tvElapsed, NULL)){
            fprintf(stderr, "Error %d: %s\n", errno, strerror(errno));
            return 0;
        }
        
    startTime = tv.tv_sec * 1000000 + tv.tv_usec;
    endTime = tvElapsed.tv_sec * 1000000 + tvElapsed.tv_usec;
    elapsedTime = endTime - startTime;
    printf("Elapsed time in micro seconds:%d\n", elapsedTime);
    
    return 0;
}

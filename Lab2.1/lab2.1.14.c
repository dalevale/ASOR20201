#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<sys/time.h>
#include<time.h>
#define STARTINGYEAR 1900
extern int errno;

int main(){

    struct timeval tv;
    struct tm *timeStructured = NULL;

    if(gettimeofday(&tv, NULL)){
        fprintf(stderr, "Error %d: %s\n", errno, strerror(errno));
        return 0;
    } 
    
    timeStructured = localtime(&tv.tv_sec);
    printf("We are in %d.\n", STARTINGYEAR + timeStructured->tm_year);
    return 0;
}

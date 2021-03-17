#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<sys/time.h>
#include<time.h>
#define STARTING_YEAR 1900
#define BUFF_SIZE 40
extern int errno;

int main(){

    char buffer[BUFF_SIZE];
    struct timeval tv;
    struct tm *timeStructured = NULL;

    if(gettimeofday(&tv, NULL)){
        fprintf(stderr, "Error %d: %s\n", errno, strerror(errno));
        return 0;
    } 
    
    timeStructured = localtime(&tv.tv_sec);
    if(timeStructured == NULL){
        fprintf(stderr, "Error in localtime() function!\n");
        return 0;
    }

    if(strftime(buffer, BUFF_SIZE, "%A, %B %d, %Y, %H:%M", timeStructured) == 0)
        fprintf(stderr, "Error in stftime() function!\n");
    else
        printf("%s\n", buffer);
    return 0;
}

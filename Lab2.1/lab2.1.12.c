#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<time.h>

extern int errno;

int main(){

    time_t seconds;
    
    seconds = time(NULL);
    if(seconds==-1)
	    fprintf(stderr, "Error %d: %s\n", errno, strerror(errno));
    else
        printf("Time is %d\n", seconds);
    return 0;
}

#include<stdio.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>

#define NUM_ERRORS 255
extern int errno;

int main(){

    int i = 0;

    for(i = 0; i <= NUM_ERRORS; i++){
	    fprintf(stderr, "Error %d: %s\n", i, strerror(i));
    }
    return 0;
}

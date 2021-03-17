#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>

extern int errno;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: ./lab2.3.7 \"command\"\n");

    }
    else if(system(argv[1])==-1){
        fprintf(stderr, "Value of errno: %d\n", errno);
	    fprintf(stderr, "String related to errno: %s\n", strerror(errno));
    }
    else
        printf("The command finalized execution.\n");
    return 0;
}
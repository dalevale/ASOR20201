#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>  

extern int errno;

int main(){

    if(setuid(0)==-1){
        fprintf(stderr, "Value of errno: %d\n", errno);
	    fprintf(stderr, "String related to errno: %s\n", strerror(errno));
    }
    return 0;
}

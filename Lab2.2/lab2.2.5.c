#include<sys/types.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>

extern int errno;

int main() {
    if(open("newFile", O_CREAT, 00645)==-1){
        fprintf(stderr, "Value of errno: %d\n", errno);
	    fprintf(stderr, "String related to errno: %s\n", strerror(errno));
    }
    
    return 0;
}
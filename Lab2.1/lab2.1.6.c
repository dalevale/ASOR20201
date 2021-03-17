#include<stdio.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>

extern int errno;

int main(){
    long sysArgMax = 0;
    long sysChildMax = 0;
    long sysFileMax = 0;

    sysArgMax = sysconf(_SC_ARG_MAX);
    sysChildMax = sysconf(_SC_CHILD_MAX);
    sysFileMax = sysconf(_SC_OPEN_MAX);

    if(sysArgMax==-1)
	    fprintf(stderr, "Error in getting _SC_ARG_MAX, erorr  %d: %s\n", errno, strerror(errno));
    else
	    printf("Max arguments: %d\n", sysArgMax);
    if(sysChildMax==-1)
	    fprintf(stderr, "Error in getting _SC_CHILD_MAX, error %d: %s\n", errno, strerror(errno));
    else
	    printf("Max child processes: %d\n", sysChildMax);
    if(sysFileMax==-1)
	    fprintf(stderr, "Error in getting _SC_OPEN_MAX, error %d: %s\n", errno, strerror(errno));
    else
	    printf("Max open files: %d\n", sysFileMax); 

    return 0;
}

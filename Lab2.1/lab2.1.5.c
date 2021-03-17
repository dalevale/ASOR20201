#include<stdio.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>
#include<sys/utsname.h>

extern int errno;

int main(){

    struct utsname unameData;

    if(uname(&unameData)==-1){
	    fprintf(stderr, "Error: %d: %s\n", errno, strerror(errno));
    } else {
        printf("System name: %s\n", unameData.sysname);
        printf("System nodename: %s\n", unameData.nodename);
        printf("System release: %s\n", unameData.release);
        printf("System version: %s\n", unameData.version);
        printf("System machine: %s\n", unameData.machine);
    }

    return 0;
}

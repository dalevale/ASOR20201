#include<signal.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>

extern int errno;

int main(int argc, char *argv[]) {
    int pid, sig;
    if(argc != 3){
        printf("Usage: ./lab2.3.10 (Pid) (Signal)\n");
    }
    else if((sscanf(argv[1], "%d", &pid) == 1) && (sscanf(argv[2], "%d", &sig) == 1)){
        if(kill(pid, sig) == -1){
            fprintf(stderr, "Value of errno: %d\n", errno);
            fprintf(stderr, "String related to errno: %s\n", strerror(errno));
        }
    }
    
    return 0;
}
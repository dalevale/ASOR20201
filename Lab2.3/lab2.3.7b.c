#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>

extern int errno;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: ./lab2.3.7 [command]\n");
    }
    else {
        char *new_argv[argc-1];
        int i;
        for(i = 0; i < argc - 1;i++)
            new_argv[i] = argv[i+1];
        if(execvp(argv[1], new_argv) == -1){
            fprintf(stderr, "Value of errno: %d\n", errno);
            fprintf(stderr, "String related to errno: %s\n", strerror(errno));
        }
        else
            printf("The command finalized execution.\n");
    }
    return 0;
}
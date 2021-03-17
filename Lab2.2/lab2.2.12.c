#include<fcntl.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>

extern int errno;

int main(int argc, char **argv) {
    if (argc != 2)
        printf("Usage: ./lab2.2.11 (filename)\n");
    else{
        int newfd = open(argv[1], O_CREAT|O_TRUNC|O_WRONLY, 0666);
        if(newfd < 0){
            fprintf(stderr, "Value of errno: %d\n", errno);
            fprintf(stderr, "String related to errno: %s\n", strerror(errno));
        }
        fflush(stdout);
        dup2(newfd, 1);
        printf("Example output.");
    }   
    return 0;
}
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<fcntl.h>

extern int errno;

int main(int argc, char *argv[]){
    int fd;

    if (argc != 3){
        printf("Usage: ./lab2.4.4.c <filename> <message>. \n");
        _exit(0);
    }
    
    fd = open(argv[1], O_WRONLY);
    char message[strlen(argv[2] + 1)];
    
    strcpy(message, argv[2]);
    message[strlen(message)] = '\n';
    
    if(fd == -1) {
        fprintf(stderr, "Value of errno: %d\n", errno);
        fprintf(stderr, "String related to errno: %s\n", strerror(errno));
        _exit(0);    
    }
    write(fd, message, strlen(message));

    return 0;
}
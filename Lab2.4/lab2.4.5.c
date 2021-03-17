#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<sys/select.h>

#define MAX_MESSAGES 2
#define BUF_SIZE 256
#define TIMEOUT 5000
extern int errno;

int main(int argc, char *argv[]){
    char message_buf[BUF_SIZE];
    int fd1, fd2;
    int changes;
    fd_set set;

    if (argc != 3) {
        printf("Usage: ./lab2.4.5 <fifofile1> <fifofile2>.\n");
        _exit(0);
    }
    while(1){
        fd1 = open(argv[1], O_RDONLY | O_NONBLOCK);
        fd2 = open(argv[2], O_RDONLY | O_NONBLOCK);

        FD_ZERO(&set);
        FD_SET(fd1, &set);
        FD_SET(fd2, &set);
        changes = select(fd2 + 1, &set, NULL, NULL, NULL);
        
        if (changes == -1){
            fprintf(stderr, "Value of errno: %d\n", errno);
            fprintf(stderr, "String related to errno: %s\n", strerror(errno));
        
        } else if (changes) {
            if(FD_ISSET(fd1, &set)){
                read(fd1, message_buf, BUF_SIZE);
                printf("From fifofile: %s", message_buf);
            }
            
            else if(FD_ISSET(fd2, &set)){
                read(fd2, message_buf, BUF_SIZE);
                printf("From fifofile2: %s", message_buf);
            }
            
        } else
            printf("No changes. r\n");
            
        close(fd1);
        close(fd2);   
    }
    
    return 0;
}
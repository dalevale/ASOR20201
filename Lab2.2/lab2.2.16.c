#include<fcntl.h>
#include<sys/stat.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
#include<sys/time.h>
#define BUFF_SIZE 10

extern int errno;

int main(int argc, char **argv) {
    int newfd;
    char buffer[BUFF_SIZE];
    struct timeval tv;
    struct tm *timeStructured = NULL;

    if (argc != 2)
        printf("Usage: ./lab2.2.16 (filename)\n");
    else{
        newfd = open(argv[1], O_CREAT|O_TRUNC|O_WRONLY, 0666);
        if(newfd < 0){
            fprintf(stderr, "Value of errno: %d\n", errno);
            fprintf(stderr, "String related to errno: %s\n", strerror(errno));
        } else {
            lockf(newfd, F_TLOCK, 0);

            if(gettimeofday(&tv, NULL)){
                fprintf(stderr, "Error %d: %s\n", errno, strerror(errno));
                lockf(newfd, F_ULOCK, 0);
                return 0;
            }
            timeStructured = localtime(&tv.tv_sec);
            if(timeStructured == NULL)
                fprintf(stderr, "Error in localtime() function!\n");
            else if (strftime(buffer, BUFF_SIZE, "%H:%M", timeStructured) == 0)
                fprintf(stderr, "Error in strftime() function!\n");
            else
                printf("%s\n", buffer);

            sleep(30);

            lockf(newfd, F_ULOCK, 0);
        }
    }   
    return 0;
}
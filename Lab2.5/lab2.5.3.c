#include<sys/socket.h>
#include<sys/types.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<netdb.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<time.h>

#define BUF_SIZE 256

extern int errno;

int main(int argc, char *argv[]){
    int fd;
    char buf[BUF_SIZE] = "";
    struct addrinfo hints;
    struct addrinfo *res;
    struct sockaddr addr;
    socklen_t addrlen;

    if(argc != 4){
        fprintf(stderr, "Usage: ./lab2.5.2 <address> <port> <message>\n");
        _exit(0);
    }

    hints.ai_flags = 0;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;


    if(getaddrinfo(argv[1], argv[2], &hints, &res) == -1 || res == NULL) {
        fprintf(stderr, "Value of errno: %d.\n", errno);
        fprintf(stderr, "String related to errno %s.\n", strerror(errno));
        _exit(0);
    }

    fd = socket(res->ai_family, res->ai_socktype, 0);

    if(fd == -1){
        fprintf(stderr, "Value of errno: %d.\n", errno);
        fprintf(stderr, "String related to errno %s.\n", strerror(errno));
        _exit(0);
    }

    if(bind(fd, (struct sockaddr *)res->ai_addr, res->ai_addrlen) == -1){
        fprintf(stderr, "Value of errno: %d.\n", errno);
        fprintf(stderr, "String related to errno %s.\n", strerror(errno));
        _exit(0);
    }

    if(res != NULL){
        sendto(fd, argv[3], strlen(argv[3]), 0, (struct sockaddr *) &addr, addrlen);
        recvfrom(fd, buf, 80, 0, (struct sockaddr *) &addr, &addrlen);
        printf("%s", buf);
    }
    close(fd);
    printf("Exiting...\n");
    return 0;
}
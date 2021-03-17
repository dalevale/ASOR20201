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
#define MAX_PENDING 1

extern int errno;

int main(int argc, char *argv[]){
    int fd, clifd, numbytes;
    char buf[BUF_SIZE] = "";
    char host[NI_MAXHOST] = "";
    char serv[NI_MAXSERV] = "";
    struct addrinfo hints, *res;
    struct sockaddr_storage addr;
    socklen_t addrlen = sizeof(addr);
    pid_t pid;

    if(argc != 3){
        fprintf(stderr, "Usage: ./lab2.5.2 <address> <port>\n");
        _exit(0);
    }

    hints.ai_flags = 0;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if(getaddrinfo(argv[1], argv[2], &hints, &res) == -1) {
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
    if(listen(fd, MAX_PENDING) == -1){
        fprintf(stderr, "Value of errno: %d.\n", errno);
        fprintf(stderr, "String related to errno %s.\n", strerror(errno));
        _exit(0);
    }
    while(1){
        clifd = accept(fd, (struct sockaddr *) &addr, &addrlen);        
        pid = fork();

        if (pid < 0){
            fprintf(stderr, "Value of errno: %d.\n", errno);
            fprintf(stderr, "String related to errno %s.\n", strerror(errno));
            _exit(0);
        } else if (pid == 0){
            getnameinfo((struct sockaddr *) &addr, addrlen, host, NI_MAXHOST, serv,
                    NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);
            printf("Connection from %s:%s\n", host, serv);
            while((numbytes = recv(clifd, buf, BUF_SIZE, 0))) {
                buf[numbytes] = '\0';
                send(clifd, buf, numbytes, 0);
            }
            close(clifd);
            _exit(0);
        } else {
            close(clifd);
        }
    }

    return 0;
}
#include<sys/socket.h>
#include<sys/types.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<netdb.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<time.h>
#include<wait.h>

#define BUF_SIZE 256

extern int errno;

int main(int argc, char *argv[]){
    int fd, numbytes;
    char buf[BUF_SIZE] = "";
    char host[NI_MAXHOST] = "";
    char serv[NI_MAXSERV] = "";
    struct addrinfo hints, *res;
    struct sockaddr_storage addr;
    socklen_t addrlen = sizeof(addr);
    pid_t pid;
    time_t dt;
    struct tm *t;
    size_t size;

    if(argc != 3){
        fprintf(stderr, "Usage: ./lab2.5.5 <address> <port>\n");
        _exit(0);
    }

    hints.ai_flags = 0;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;

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
    pid = fork();
    
    switch(pid){
        case -1:
            fprintf(stderr, "Value of errno: %d.\n", errno);
            fprintf(stderr, "String related to errno %s.\n", strerror(errno));
            break;
        case 0:
        while(1){
            numbytes = recvfrom(fd, buf, BUF_SIZE, 0, (struct sockaddr *) &addr, &addrlen);
            buf[numbytes-1] = '\0';
            getnameinfo((struct sockaddr *) &addr, addrlen, host, NI_MAXHOST, serv,
                            NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);
            printf("PID %d: %d bytes from %s:%s\n", getpid(), numbytes, host, serv);

            if(strcmp(buf, "t") == 0){
                time(&dt);
                t = localtime(&dt);
                size = strftime(buf, BUF_SIZE, "%H:%M:%S %p", t);
                buf[size] = '\0';
                sendto(fd, buf, size, 0, (struct sockaddr *) &addr, addrlen);
            }
            else if(strcmp(buf, "d") == 0){
                time(&dt);
                t = localtime(&dt);
                size = strftime(buf, BUF_SIZE, "%Y-%m-%d", t);
                buf[size] = '\0';
                sendto(fd, buf, size, 0, (struct sockaddr *) &addr, addrlen);
            } else if(strcmp(buf, "q") == 0){
                close(fd);
                break;
            }
            else 
                fprintf(stderr, "Command not supported %s\n", buf);
        }
        break;
            
        default:
            wait(NULL);
            printf("Exiting...\n");
    }
    return 0;
}
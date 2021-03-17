#include<sys/socket.h>
#include<sys/types.h>
#include<sys/select.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<netdb.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<time.h>

#define BUF_SIZE 256

extern int errno;

int print_message(char *buf){
    time_t dt;
    struct tm *t;
    size_t size = 0;
    if(strcmp(buf, "t") == 0){
        time(&dt);
        t = localtime(&dt);
        size = strftime(buf, BUF_SIZE, "%H:%M:%S %p", t);
        buf[size] = '\0';
    }
    else if(strcmp(buf, "d") == 0){
        time(&dt);
        t = localtime(&dt);
        size = strftime(buf, BUF_SIZE, "%Y-%m-%d", t);
        buf[size] = '\0';
    } else
        printf("Command not supported %s\n", buf);

    return size;
}


int main(int argc, char *argv[]){
    int fd, changes, numbytes;
    fd_set set;
    char buf[BUF_SIZE] = "";
    char host[NI_MAXHOST] = "";
    char serv[NI_MAXSERV] = "";
    struct addrinfo hints, *res;
    struct sockaddr_storage addr;
    socklen_t addrlen = sizeof(addr);

    if(argc != 3){
        fprintf(stderr, "Usage: ./lab2.5.4 <address> <port>\n");
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
    while(1){
        int size = 0;
        FD_ZERO(&set);
        FD_SET(0, &set);
        FD_SET(fd, &set);
        changes = select(fd + 1, &set, NULL, NULL, NULL);

        if (changes == -1){
            fprintf(stderr, "Value of errno: %d\n", errno);
            fprintf(stderr, "String related to errno: %s\n", strerror(errno));        
        } else if(FD_ISSET(0, &set)){
            scanf("%s", buf);
            fflush(0);
            if(strcmp(buf, "q") == 0)
                break;
            size = print_message(buf);
            if(size)
                printf("%s\n", buf);
        } else if (FD_ISSET(fd, &set)) {
            numbytes = recvfrom(fd, buf, BUF_SIZE, 0, (struct sockaddr *) &addr, &addrlen);
            buf[numbytes-1] = '\0';
            getnameinfo((struct sockaddr *) &addr, addrlen, host, NI_MAXHOST, serv,
                            NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);
            printf("%d bytes from %s:%s\n", numbytes, host, serv);
            if(strcmp(buf, "q") == 0)
                break;
            size = print_message(buf);
            sendto(fd, buf, size, 0, (struct sockaddr *) &addr, addrlen);
        } else
            printf("No changes.\n");
    }
    close(fd);
    printf("Exiting...\n");
    return 0;
}
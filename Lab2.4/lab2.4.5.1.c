#include<sys/socket.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>

extern int errno;

int main(){

    struct addrinfo hints, *res;
    char service[] = "http";
    char node[] = 192.168.0.100

    if(getaddrinfo(node, service, &hints, &res) == -1) {
        fprintf(stderr, "Value of errno: %d.\n", errno);
        fprintf(stderr, "String related to errno %s.\n", strerror(errno));
        _exit(0);
    }

}
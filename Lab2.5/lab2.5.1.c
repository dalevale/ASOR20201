#include<sys/socket.h>
#include<sys/types.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<netdb.h>
#include<unistd.h>
#include<arpa/inet.h>

extern int errno;

char * get_ip_str (const struct sockaddr *sa, char *s, size_t maxlen){
    switch(sa->sa_family){
        case AF_INET:
            inet_ntop(AF_INET, &(((struct sockaddr_in *)sa)->sin_addr), s, maxlen);
            break;
        case AF_INET6:
            inet_ntop(AF_INET6, &(((struct sockaddr_in6 *)sa)->sin6_addr), s, maxlen);
            break;
        default:
            strncpy(s, "Unknown AF", maxlen);
            return NULL;
    }
    return s;
}

int main(int argc, char *argv[]){

    struct addrinfo hints;
    struct addrinfo *res, *p;
    char service[] = "http";
    
    if(argc < 2){
        printf("Usage: ./lab2.5.1 <name/host/ipaddr/ipaddr6>.\n");
        _exit(0);
    }
    if(getaddrinfo(argv[1], service, &hints, &res) == -1) {
        fprintf(stderr, "Value of errno: %d.\n", errno);
        fprintf(stderr, "String related to errno %s.\n", strerror(errno));
        _exit(0);
    }
    if(res == NULL){
        printf("getaddrinfo(): Name or service not known.\n");
        _exit(0);
    }
    for(p = res; p != NULL; p = p->ai_next) { 
        char buffer[res->ai_addrlen];
        if(get_ip_str(res->ai_addr, buffer, res->ai_addrlen) == NULL)
            printf("Unable to fetch ip address string.\n");
        else{
            printf("%s    %d    %d\n", buffer, res->ai_family, res->ai_socktype);
        }        
        res = res->ai_next;
    }   
    return 0;
}
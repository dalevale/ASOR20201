#include<signal.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>

extern int errno;
int num_int = 0, num_tstp = 0;
void handle_error(){
    fprintf(stderr, "Value of errno: %d\n", errno);
    fprintf(stderr, "String related to errno: %s\n", strerror(errno));
    _exit(0);
}

void handler(int signum){
    if(signum == SIGINT)
        num_int++;
    if(signum == SIGTSTP)
        num_tstp++;
}

int main() {
    struct sigaction sa;

    sa.sa_flags = SA_SIGINFO;
    if (sigemptyset(&sa.sa_mask) == -1)
        handle_error();
    sa.sa_handler = handler;
    if (sigaction(SIGINT, &sa, NULL) == -1)
        handle_error();
    if (sigaction(SIGTSTP, &sa, NULL) == -1)
        handle_error();

    while (num_int + num_tstp != 10);

    printf("Number of SIGINT signals receieved: %d\n", num_int);
    printf("Number of SIGTSTP signals receieved: %d\n", num_tstp);

    return 0;
}
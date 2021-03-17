#include<signal.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>

extern int errno;

void handle_error(){
    fprintf(stderr, "Value of errno: %d\n", errno);
    fprintf(stderr, "String related to errno: %s\n", strerror(errno));
    _exit(0);
}

void handler(int signum){
    if(signum == SIGALRM){
        unlink("lab2.3.13");
        printf("SIGALRM received. File deleted.\n");
        }
    else if(signum == SIGUSR1)
        printf("SIGUSR1 received. File deletion canceled\n");
}

int main(int argc, char *argv[]) {
    int num = 0;

    if((argc != 2) || (sscanf(argv[1], "%d", &num) != 1) || (num < 0))
        printf("Usage: ./lab2.3.13 <seconds> \n");

    else {
        pid_t pid = getpid();
        struct sigaction sa;

        sa.sa_flags = SA_SIGINFO;
        if (sigfillset(&sa.sa_mask) == -1)
            handle_error(); 
        else if (sigdelset(&sa.sa_mask, SIGALRM) == -1)
            handle_error();
        else if (sigdelset(&sa.sa_mask, SIGUSR1) == -1)
            handle_error();
        sa.sa_handler = handler;
        if (sigaction(SIGALRM, &sa, NULL) == -1)
            handle_error();
        sa.sa_handler = handler;
        if (sigaction(SIGUSR1, &sa, NULL) == -1)
            handle_error();

        printf("Process %d is deleting lab2.3.13 executable in %d second(s).\n", pid, num);   
        alarm(num);
        (sigsuspend(&sa.sa_mask));
    }
    
    return 0;
}

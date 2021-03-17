#include<signal.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>

extern int errno;

void handle_error(){
    fprintf(stderr, "Value of errno: %d\n", errno);
    fprintf(stderr, "String related to errno: %s\n", strerror(errno));
    _exit(0);
}

int main() {
    sigset_t blk_set, pending_set;

    printf("PID: %d\n", getpid());
    if (sigemptyset(&blk_set) == -1)
        handle_error();
    else if (sigaddset(&blk_set, SIGINT) == -1)
        handle_error();
    else if (sigaddset(&blk_set, SIGTSTP) == -1)
        handle_error();
    else if (sigprocmask(SIG_BLOCK, &blk_set, NULL) == -1)
        handle_error();
    
    int sec;
    if(sscanf(getenv("SLEEP_SEC"), "%d", &sec) == 1)
        sleep(sec);
    if(sigpending(&pending_set) == -1)
        handle_error();
    if (sigemptyset(&blk_set) == -1)
        handle_error();
    if (sigprocmask(SIG_UNBLOCK, &blk_set, NULL) == -1)
        handle_error();
    
    if(sigismember(&pending_set, SIGINT))
        printf("SIGINT signal was sent while blocked.\n");
    if(sigismember(&pending_set, SIGTSTP))
        printf("SIGTSTP signal was sent while blocked.\n");

    printf("Program has finished its execution.\n");
    
    return 0;
}
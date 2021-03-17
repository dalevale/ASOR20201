#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>

extern int errno;

int main(int argc, char *argv[]) {
    if (argc > 1) {
        fprintf(stderr, "Usage: ./lab2.3.7\n");
        _exit(0);
    }
    int newstdout = open("/tmp/daemon.out", O_CREAT|O_TRUNC|O_WRONLY, 0666);
    int newstdin = open("/dev/null", O_CREAT|O_TRUNC|O_WRONLY, 0666);
    int newstderr = open("/tmp/daemon.err", O_CREAT|O_TRUNC|O_WRONLY, 0666);
    char *new_argv[argc-1];
    pid_t pid;
    char *path = "/tmp";
    new_argv[0] = "./sample";
    new_argv[1] = NULL;

    if(newstdout < 0){
        fprintf(stderr, "Value of errno: %d\n", errno);
        fprintf(stderr, "String related to errno: %s\n", strerror(errno));
        _exit(0);
    } else if(newstdout < 0){
        fprintf(stderr, "Value of errno: %d\n", errno);
        fprintf(stderr, "String related to errno: %s\n", strerror(errno));
        _exit(0);
    } else if(newstdout < 0){
        fprintf(stderr, "Value of errno: %d\n", errno);
        fprintf(stderr, "String related to errno: %s\n", strerror(errno));
        _exit(0);
    }
    fflush(stdin);
    fflush(stdout);
    fflush(stderr);
    dup2(newstdin, 0);
    dup2(newstdout, 1);
    dup2(newstderr, 2);

    if(chdir(path) == -1){
        fprintf(stderr, "Value of errno: %d\n", errno);
        fprintf(stderr, "String related to errno: %s\n", strerror(errno));
    }
    pid = fork();
    switch (pid) {
        case -1:
            fprintf(stderr, "Value of errno: %d\n", errno);
            fprintf(stderr, "String related to errno: %s\n", strerror(errno));
            break;
        case 0:
            pid = getpid();
            pid_t sid = setsid();
            pid_t pgid = sid;
            printf("Pid: %d\n", pid);    
            printf("Pgid: %d\n", pgid);
            printf("Sid: %d\n", sid);
            sleep(10);
            break;
            printf("Child PID: %d\n", getpid());
            if(execvp(new_argv[0], new_argv) == -1){
                fprintf(stderr, "Value of errno: %d\n", errno);
                fprintf(stderr, "String related to errno: %s\n", strerror(errno));
            }
            while(1);
            break;
        default:
            break;
    }
    return 0;
}
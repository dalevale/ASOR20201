#include<unistd.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<wait.h>

extern int errno;

void handle_error(){
    fprintf(stderr, "Value of errno: %d\n", errno);
    fprintf(stderr, "String related to errno: %s\n", strerror(errno));
    _exit(0);
}


int main(int argc, char *argv[]){
    int pipefd[2];
    char *argv1[3];
    char *argv2[3];
    pid_t pid;
    if(argc != 5){
        printf("Usage: ./lab2.4.1 (command1) (argument1) (command2) (argument2). \n");
        _exit(0);
    } else if(pipe(pipefd) == -1)
        handle_error();
    else {
        pid = fork();
        if (pid == -1)
            handle_error();
        else if (pid == 0){
            close(pipefd[1]);
            dup2(pipefd[0], 0);
            argv1[0] = argv[3];
            argv1[1] = argv[4];
            argv1[2] = NULL; 
            if(execvp(argv1[0], argv1) == -1)
                handle_error();
            else {
                close(pipefd[0]);
                _exit(0);
            }
            close(pipefd[0]);
        } else {
            close(pipefd[0]);
            dup2(pipefd[1], 1); 
            argv2[0] = argv[1];
            argv2[1] = argv[2]; 
            argv2[2] = NULL;
            if(execvp(argv2[0], argv2) == -1)
                handle_error();
            wait(NULL);
            close(pipefd[1]);
        }
    }
    return 0;
}
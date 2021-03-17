#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<wait.h>

#define MAX_MESSAGES 2
#define BUF_SIZE 32

extern int errno;


void handle_error(){
    fprintf(stderr, "Value of errno: %d\n", errno);
    fprintf(stderr, "String related to errno: %s\n", strerror(errno));
    _exit(0);
}


int main(int argc, char *argv[]){
    int p_c[2], c_p[2];
    char message_buf[BUF_SIZE];
    char send_buf[BUF_SIZE], recv_buf[BUF_SIZE];
    pid_t pid;
    int num_messages=0;

    if((pipe(p_c) == -1) || pipe(c_p) == -1)
        handle_error();
    pid = fork();

    if (pid == -1) 
        handle_error();
    else if (pid == 0){
        close(p_c[1]);
        close(c_p[0]);

        while(num_messages < MAX_MESSAGES){
            if(read(p_c[0], message_buf, BUF_SIZE) != 0){
                num_messages++;
                printf("%s\n", message_buf);
                if (num_messages == MAX_MESSAGES)
                    write(c_p[1], "q", 1);
                else
                    write(c_p[1], "r", 1);
                sleep(1);
            }
        }
        close(p_c[0]);
        close(c_p[1]);
        _exit(0);
        
    } else {
        close(p_c[0]);
        close(c_p[1]);

        while(strcmp("q", recv_buf) != 0){
            if (scanf("%s", send_buf) == -1) 
                handle_error();
            else {       
                write(p_c[1], send_buf, strlen(send_buf));
                while(read(c_p[0], recv_buf, 1) == 0);
            }
        }
        close(p_c[1]);
        close(c_p[0]);
        wait(NULL);
        printf("Program terminated.\n");
        _exit(0);
    }
    return 0;
}
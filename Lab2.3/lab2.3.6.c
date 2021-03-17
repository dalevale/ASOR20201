    #include<unistd.h>
    #include<stdio.h>
    #include<errno.h>
    #include<string.h>

    extern int errno;

    int main() {
        pid_t pid, mypid, pgid, sid;
        char *path = "/tmp";

        if(chdir(path) == -1){
            fprintf(stderr, "Value of errno: %d\n", errno);
            fprintf(stderr, "String related to errno: %s\n", strerror(errno));
        }
        
        else {
            pid = fork();
            mypid = getpid();
            switch (pid) {
                case -1:
                    fprintf(stderr, "Value of errno: %d\n", errno);
                    fprintf(stderr, "String related to errno: %s\n", strerror(errno));
                    break;
                case 0:
                    pgid = sid = setsid();
                    printf("Pid: %d\n", mypid);    
                    printf("Pgid: %d\n", pgid);
                    printf("Sid: %d\n", sid);
                    sleep(10);
                    break;
                default:
                    pgid = getpgid(pid);
                    sid = getsid(pid);
                    printf("Parent Pid: %d\n", mypid);    
                    printf("Parent Pgid: %d\n", pgid);
                    printf("Parent Sid: %d\n", sid);
                    break;
            }
        }
        return 0;
    }
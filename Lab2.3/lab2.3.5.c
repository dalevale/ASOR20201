#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<sys/resource.h>

#define BUFF_SIZE 100

extern int errno;

int main() {
    pid_t pid, pgid, sid;
    char path[BUFF_SIZE];
    struct rlimit rlim;
    int max_nofile, curr_nofile;

    pid = getpid();
    pgid = getpgid(pid);
    sid = getsid(pid);
    if(getcwd(path, BUFF_SIZE) == NULL){
        fprintf(stderr, "Value of errno: %d\n", errno);
	    fprintf(stderr, "String related to errno: %s\n", strerror(errno));
    }
    else if(getrlimit(RLIMIT_NOFILE, &rlim) == -1) {
        fprintf(stderr, "Value of errno: %d\n", errno);
	    fprintf(stderr, "String related to errno: %s\n", strerror(errno));
    }
    else {
        max_nofile = rlim.rlim_max;
        curr_nofile = rlim.rlim_cur;
        printf("Pid: %d\n", pid);    
        printf("Pgid: %d\n", pgid);
        printf("Sid: %d\n", sid);
        printf("Current Working Directory: %s\n", path);
        printf("Current opened files limit: %d\n", curr_nofile);
        printf("Max opened files limit: %d\n", max_nofile);
    }
    return 0;
}
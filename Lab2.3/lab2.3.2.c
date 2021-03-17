#include<sched.h>
#include<sys/resource.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>

extern int errno;

int main() {
    pid_t pid;
    int policy = 0, pmin = 0, pmax = 0;
    struct sched_param param;

    pid = getpid();
    policy = sched_getscheduler(pid);
    pmin = sched_get_priority_min(policy);
    pmax = sched_get_priority_max(policy);
    if(sched_getparam(pid, &param) == -1){
        fprintf(stderr, "Value of errno: %d\n", errno);
	    fprintf(stderr, "String related to errno: %s\n", strerror(errno));
    }
    else if(pmin == -1){
        fprintf(stderr, "Value of errno: %d\n", errno);
	    fprintf(stderr, "String related to errno: %s\n", strerror(errno));
    }
    else if(pmax == -1){
        fprintf(stderr, "Value of errno: %d\n", errno);
	    fprintf(stderr, "String related to errno: %s\n", strerror(errno));
    }
    else {
        printf("Pid: %d\n", pid);
        switch(policy){
            case SCHED_RR:
                printf("Policy: Round Robin\n");
                break;
            case SCHED_FIFO:
                printf("Policy: First In First Out\n");
                break;
            /*case SCHED_BATCH:
                printf("Policy: Batch");
                break;
            case SCHED_IDLE:
                printf("Policy: Idle");
                break;                */
            case SCHED_OTHER:
                printf("Policy: Other\n");
                break;
        }
        printf("Priority: %d\n", param.sched_priority);
        printf("Minimum priority: %d\n", pmin);
        printf("Maximum priority: %d\n", pmax);
    }
    
    
    return 0;
}
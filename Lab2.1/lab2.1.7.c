#include<stdio.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>

extern int errno;

int main(){
    
    long linkMax = 0;
    long pathSizeMax = 0;
    long fileNameMax = 0;

    linkMax = pathconf("/",_PC_LINK_MAX);
    pathSizeMax = pathconf("/", _PC_PATH_MAX);
    fileNameMax = pathconf("/", _PC_NAME_MAX);

    if(linkMax==-1)
        fprintf(stderr, "Error in getting _SC_ARG_MAX, erorr  %d: %s\n", errno, strerror(errno));
    else
        printf("Max file links: %d\n", linkMax);
    if(pathSizeMax==-1)
        fprintf(stderr, "Error in getting _SC_CHILD_MAX, error %d: %s\n", errno, strerror(errno));
    else
        printf("Max path size: %d\n", pathSizeMax);
    if(fileNameMax==-1)
        fprintf(stderr, "Error in getting _SC_OPEN_MAX, error %d: %s\n", errno, strerror(errno));
    else
        printf("Max length filename: %d\n", fileNameMax);

    return 0;
}

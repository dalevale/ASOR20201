#include<sys/stat.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>

extern int errno;

int main(int argc, char **argv) {
    struct stat fileStat;
    if (argc != 2)
        printf("Usage: ./lab2.2.11 (filename)\n");
    else if(stat(argv[1], &fileStat)==-1){
        fprintf(stderr, "Value of errno: %d\n", errno);
	    fprintf(stderr, "String related to errno: %s\n", strerror(errno));
    } else {
        if (S_ISREG(fileStat.st_mode)){
            char hardLink[strlen(argv[1])];
            char symLink[strlen(argv[1])];
            strcpy(hardLink, argv[1]);
            strcpy(symLink, argv[1]);
            strcat(hardLink, ".hard");
            strcat(symLink, ".sym");
            if(link(argv[1], hardLink)==-1){
                fprintf(stderr, "1Value of errno: %d\n", errno);
                fprintf(stderr, "String related to errno: %s\n", strerror(errno));
            }
            if(symlink(argv[1], symLink)==-1){
                fprintf(stderr, "2Value of errno: %d\n", errno);
                fprintf(stderr, "String related to errno: %s\n", strerror(errno));
            }
        }
        else 
            printf("%s is not a Regular File.\n", argv[1]);
    }
    
    return 0;
}
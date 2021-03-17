#include<sys/stat.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<time.h>

extern int errno;

int main(int argc, char **argv) {
    struct stat fileStat;
    if (argc != 2)
        printf("Usage: ./lab2.2.9 (filename)\n");
    else if(stat(argv[1], &fileStat)==-1){
        fprintf(stderr, "Value of errno: %d\n", errno);
	    fprintf(stderr, "String related to errno: %s\n", strerror(errno));
    } else {
        printf("File: '%s'\n", argv[1]);
        printf("Major number: %x\n", (unsigned int) fileStat.st_dev>>8);
        printf("Minor number: %x\n", (unsigned int) fileStat.st_dev & 0xff);
        printf("Inode number: %d\n", (unsigned int) fileStat.st_ino);
        if (S_ISREG(fileStat.st_mode))
            printf("File type: Regular File\n");
        else if (S_ISDIR(fileStat.st_mode))
            printf("File type: Directory\n");
        else if (S_ISLNK(fileStat.st_mode))
            printf("File type: Symbolic Link\n");
        printf("Last file access: %s\n", ctime(&fileStat.st_atime));

    }
    
    return 0;
}
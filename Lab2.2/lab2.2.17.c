#include<fcntl.h>
#include<sys/stat.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
#include<dirent.h>

extern int errno;

int main(int argc, char **argv) {
    DIR *dir;
    struct dirent *dent;
    if (argc != 2)
        printf("Usage: ./lab2.2.17 (filename)\n");
    else if ((dir = opendir(argv[1])) != NULL) {
        while((dent = readdir(dir)) != NULL) {
            int len = strlen(argv[1]) + 1 + strlen(dent->d_name);
            char aux[len];
            if(strcmp(dent->d_name, ".")==0 || strcmp(dent->d_name, "..")==0)
                continue;    
            else if (dent->d_type == DT_DIR)
                printf("%s/\n", dent->d_name); 
            else if (dent->d_type == DT_LNK){
                printf("%s->\n", dent->d_name);
            }
            else if (dent->d_type == DT_REG){
                strcpy(aux, argv[1]);
                strcat(aux, "/");
                strcat(aux, dent->d_name);
                printf("%s\n", aux);
                if (access(aux, X_OK) < 0)
                    printf("%s\n", dent->d_name);
                else
                    printf("%s*\n", dent->d_name);
            }
        }
    }
    closedir(dir);
    return 0;
}
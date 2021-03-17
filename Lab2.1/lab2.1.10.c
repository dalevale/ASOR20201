#include<stdio.h>
#include<unistd.h>
#include<pwd.h>

int main(){

    struct passwd *userInfo;

    userInfo = getpwuid(getuid());
    printf("Id: %s\n", userInfo->pw_name);
    printf("Home directory: %s\n", userInfo->pw_dir);
    printf("User information: %s\n", userInfo->pw_gecos);
    return 0;
}

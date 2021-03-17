#include<stdio.h>
#include<unistd.h>
#include<pwd.h>

int main(){

    struct passwd *userInfo;

    userInfo = getpwuid(getuid());
    printf("Id: %d\n", userInfo->pw_uid);

    return 0;
}

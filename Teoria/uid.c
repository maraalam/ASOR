#include <unistd.h>     //getuid, setuid ...
#include <sys/types.h>

#include <stdio.h>       //printf


int main(int argc,char **argv){

    uid_t uid = getuid();
    gid_t gid = getgid();
    uid_t euid = geteuid();
    gid_t egid = getegid();

    printf("uid: %d\n",uid);
    printf("gid: %d\n",gid);
    printf("euid: %d\n",euid);
    printf("egid: %d\n",egid);


    return 0;
}

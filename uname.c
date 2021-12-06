#include <sys/utsname.h> //uname

#include <stdio.h>       //error
#include <errno.h>
#include <string.h>

int main (int argc, char **argv){

    struct utsname sys_info;

    //error handling
    if (uname(&sys_info) == -1){
        int error = errno;
        perror("uname");
        exit(1);
    }

    //This could be done directly in the printf
    char *sysname  = sys_info.sysname;
    char *nodename = sys_info.nodename;
    char *release  = sys_info.release;
    char *version  = sys_info.version;
    char *machine  = sys_info.machine;
    char *domainname = "";
    #ifdef _GNU_SOURCE
        domainname = sys_info.domainname;
    #endif

    printf("system name = %s\n", sysname);
    printf("node name   = %s\n", nodename);
    printf("release     = %s\n", release);
    printf("version     = %s\n", version);
    printf("machine     = %s\n", machine);
    printf("domain name = %s\n", domainname);


    return 0;
}
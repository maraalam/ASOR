#include <sys/types.h>     
#include <pwd.h>
#include <unistd.h>      //uid

#include <stdio.h>       //prinf

int main(int argc, char **argv){

    uid_t uid = getuid();

    struct passwd *pw = getpwnam(uid);

    if(pw){//pw!=NULL

        printf("pw_name : %s\n", &pw.pw_name);
        printf("pw_passwd : %s\n", &pw.pw_passwd);
        printf("pw_uid : %d\n", &pw.pw_uid);
        printf("pw_gid : %d\n", &pw.pw_gid);
        printf("pw_gecos : %s\n", &pw.pw_gecos);
        printf("pw_dir : %s\n", &pw.pw_dir);
        printf("pw_shell : %s\n", &pw.pw_shell);

    }

    return 0;
}

#include <stdio.h>      //error
#include <errno.h>
#include <string.h>

#include <sys/time.h>   //priority
#include <sys/resource.h>


#include <sys/types.h>  //pid
#include <unistd.h>


int main(int argc, char *argv[]){



    pid_t pid = getpid();
    int priority = getpriority(PRIO_PROCESS, pid);

    printf("PID : %d\n Priority : %d\n\n", pid, priority);



    if(setpriority(PRIO_PROCESS, pid, -10)==-1){
        perror("setpriority");
        exit(1);
    } 


    int new_priority = getpriority(PRIO_PROCESS, pid);

    printf("PID : %d\n Priority : %d\n\n", pid, new_priority);





    return 0;
}
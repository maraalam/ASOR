#include <stdio.h>      //error
#include <errno.h>
#include <string.h>

#include <sched.h>      //sched


#include <sys/types.h>  //pid
#include <unistd.h>


int main(int argc, char *argv[]){

    pid_t pid = getpid();


    /*SCHED_GETSCHEDULER*/
    int policy;
    if((policy = sched_getscheduler(pid)) == -1){
        perror("sched_getscheduler 1");
        exit(1);
    }

    printf("pid : %ld\nPolicy : %d\n", pid, policy);



    /*SCHED_GETPARAM*/
    struct sched_param parameters;

    if(sched_getparam(pid,&parameters) == -1){
        perror("sched_getparam");
        exit(1);
    }
    parameters.sched_priority = 3;


    /*SCHED_SETSCHEDULER*/
    if(sched_setscheduler(pid,2,&parameters) == -1){
        perror("sched_setscheduler");
        exit(1);
    }


    /*SCHED_GETSCHEDULER*/
    int new_policy;
    if((new_policy = sched_getscheduler(pid)) == -1){
        perror("sched_getscheduler 2");
        exit(1);
    }


    printf("pid : %ld\nNew Policy : %d\n", pid, new_policy);


    return 0;
}
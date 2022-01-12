#include <stdio.h>      //error
#include <errno.h>
#include <string.h>

#include <sched.h>      //sched


#include <sys/types.h>  //pid
#include <unistd.h>


int main(int argc, char *argv[]){

    pid_t fork_pid = fork();


    if(fork_pid == 0){ //CHILD PRCESS
        pid_t pid = getpid();
        int policy;

        if((policy = sched_getscheduler(pid)) == -1){
            perror("sched_getscheduler");
            exit(1);
        }

        printf("CHILD with pid : %ld. Policy : %d\n",pid,policy);
    }

    else if(fork_pid >0){//PARENT PROCESS
        pid_t pid = getpid();
        int policy;

        if((policy = sched_getscheduler(pid)) == -1){
            perror("sched_getscheduler");
            exit(1);
        }

        printf("PARENT with pid : %ld. Policy : %d\n",pid,policy);

        wait(NULL);
    }
    else{
        perror("fork");
        exit(1);
    }


    return 0;
}
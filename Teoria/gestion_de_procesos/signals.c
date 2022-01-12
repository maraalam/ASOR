#include <stdio.h>      //error
#include <errno.h>
#include <string.h>

#include <signal.h>

#include <sys/types.h>  //pid
#include <unistd.h>

#include <stdlib.h>     //getenv

int main (int argc,char *argv[]){

    pid_t pid = getpid();

    sigset_t set;

    sigemptyset(&set); //Inicializo el conjunto vacio
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGTSTP);


    if(sigprocmask(SIG_SETMASK,&set,NULL) == -1){
        perror("sigprocmask");
        exit(1);
    }

    
    int sleep_secs = (int) getenv("SLEEP_SECS");
    printf("Process sleeping for %d seconds\n", sleep_secs);
    sleep(sleep_secs);


    sigset_t set_pend;
    sigpening(&set_pend);

    if(sigismember(&set_pend,SIGINT)==1){//RETURN 1 IF MEMBER OF SET
        printf("Signal SIGINT receive\n");
    }

    if(sigismember(&set_pend,SIGTSTP)==1){//RETURN 1 IF MEMBER OF SET
        printf("Signal SIGTSTP receive\n");
    }


    sigprocmask(SET_UNBLOCK,&set,NULL);


    return 0;
}


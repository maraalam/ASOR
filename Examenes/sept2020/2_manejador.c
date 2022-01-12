#include <signal.h>
#include <stdio.h>
#include <errno.h>


volatile int sigint_n=0;
volatile int sigtstp_n=0;

void handler(int segnal){
    if(segnal==SIGINT) sigint_n++;
    if(segnal==SIGTSTP) sigtstp_n++;
}


int main(int argc, char *argv[]){


    //SIGINT
    struct sigaction sigint;
    if(sigaction(SIGINT,NULL,&sigint) == -1){
        perror("sigaction SIGINT");
        exit(1);
    }

    sigint.sa_handler = handler;

    if(sigaction(SIGINT,&sigint,NULL) == -1){
        perror("sigaction SIGINT");
        exit(1);
    }


    //SIGTSTP
    struct sigaction sigtstp;
    if(sigaction(SIGTSTP,NULL,&sigtstp) == -1){
        perror("sigaction SIGTSTP");
        exit(1);
    }

    sigtstp.sa_handler = handler;

    if(sigaction(SIGTSTP,&sigtstp,NULL) == -1){
        perror("sigaction SIGTSTP");
        exit(1);
    }



    sigset_t set;
    sigemptyset(&set);


    while(sigint_n + sigtstp_n < 10)
        sigsuspend(&set);
    
    printf("Captured %i SIGINT signals\n",sigint_n);
    printf("Captured %i SIGTSTP signals\n",sigtstp_n);



    return 0;
}
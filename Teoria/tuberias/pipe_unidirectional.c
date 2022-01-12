#include <stdio.h>      //error
#include <errno.h>
#include <string.h>     

#define _GNU_SOURCE      //pipe       
#include <fcntl.h>              
#include <unistd.h>




int main(int argc, char *argv[]){

    if(argc < 5){
        fprintf(stderr, "Incorrect parameters number\n");
        exit(1);
    }

    int fd[2];

    if(pipe(fd)==-1){
        perror("pipe");
        exit(1);
    }

    pid_t pid = fork();

    if(pid > 0){//Parent

        close(fd[0]);//Close read

        dup2(fd[1], 1);

        execlp(argv[1],argv[1],argv[2],NULL);

        wait(NULL);
        close(fd[1]);


    }else if(pid == 0){//Child

        close(fd[1]);//Close write

        dup2(fd[0], 0);

        execlp(argv[3],argv[3],argv[4],NULL);

    }else{
        perror("fork");
        exit(1);
    }


    return 0;
}
#include <stdio.h>      //error
#include <errno.h>
#include <string.h>     

#define _GNU_SOURCE      //pipe       
#include <fcntl.h>              
#include <unistd.h>



int main(int argc, char *argv[]){

    const int RD = 0, WR = 1;


    int p_h[2], h_p[2];

    if(pipe(p_h) == -1){
        perror("pipe");
        exit(1);
    }

    if(pipe(h_p) == -1){
        perror("pipe");
        exit(1);
    }


    pid_t pid = fork();


    if(pid > 0){ //Parent

        close(p_h[RD]);
        close(h_p[WR]);

        char message[1],message_father[255];
        message[0] = 'l';

        while(message[0] != 'q'){
            size_t bytes = read(0,message_father,255);
            printf("[PARENT] Receive shell message : %s\n", message_father);
            write(p_h[WR], message_father, bytes);

            read(h_p[RD], message, 1);
            printf("[PARENT] Receive child message : %s\n", message);
        }



        wait(NULL);

        close(p_h[WR]);
        close(h_p[RD]);
        

    } else if (pid == 0){ //Child

        close(p_h[WR]);
        close(h_p[RD]);

        char message[255];
        int i;
        char message_child[1];
        message_child [0] = 'l';

        for(i = 0; i < 10; i++){
            size_t bytes = read(p_h[RD], message, 255);
            message[bytes] = "\0";

            printf("[CHILD] Receive parent message : %s\n", message);
            sleep(1);
            
            if(i<9){
                write(h_p[WR],message_child,1);
            }
            else{
                message_child[0] = 'q';
                write(h_p[WR], message_child, 1);
            }
        }

    } else{
        perror("fork");
        exit(1);
    }


    return 0;
}
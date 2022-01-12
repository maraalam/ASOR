#include <stdio.h>      //error
#include <errno.h>
#include <string.h>    

#include <fcntl.h>       //flags

#include <sys/select.h>  //select

#include <sys/types.h>   //mkfifo
#include <sys/stat.h> 



int main(int argc, char *argv[]){


    mkfifo("fifo1",0777);
    mkfifo("fifo2",0777);

    int fifo1, fifo2;
    
    char buffer[256];
    int stop = 0;
    int nfds = 0;
    int fifo;

    while(stop != -1){

        if((fifo1 = open("fifo1", O_RDONLY | O_NONBLOCK)) == -1 || 
            (fifo2 = open("fifo2", O_RDONLY | O_NONBLOCK)) == -1){
            perror("open");
            exit(1);
        }

        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(fifo1, &readfds);
        FD_SET(fifo2, &readfds);

         
        if(fifo1 < fifo2)
            nfds = fifo2 + 1;
        else
            nfds = fifo1 + 1;

        stop = select(nfds, &readfds, NULL, NULL, NULL);

        if(stop > 0){
            if (FD_ISSET(fifo1, &readfds)){
                fifo = fifo1;
            }
            else if (FD_ISSET(fifo2, &readfds)){
                fifo = fifo2;
            }

            size_t bytes = read(fifo, buffer, 256);
            buffer[bytes] = '\0';

            if(fifo == fifo1){
                printf("[FIFO1] Message : %s\n", buffer);
            }
            else if(fifo == fifo2){
                printf("[FIFO2] Message : %s\n", buffer);
            }

        }
        else if(stop == -1){
            perror("select");
        }
        else{
            printf("Nothing receive\n");
        }


    }

    close(fifo1);
    close(fifo2);

    return 0;
}
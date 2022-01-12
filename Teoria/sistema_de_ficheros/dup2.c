#include <sys/types.h>  //stat
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>      //error

int main(int argc, char *argv[]){

    int mask = umask(0022);
    int fd = open("redireccion.txt", O_CREAT | O_RDWR, 0777);


    if(dup2(fd, 1) == -1){
        perror("dup");
        exit(1);
    }
    
    printf("Salida redirigida\n");

    close(fd);

    return 0;
}
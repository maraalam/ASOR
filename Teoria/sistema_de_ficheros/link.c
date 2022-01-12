#include <sys/types.h>  //stat
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>      //error
#include <errno.h>
#include <string.h>


int main(int argc, char *argv[]){

    if(argc < 2){
        fprintf(stderr,"[ERROR] Incorrect parameters\n");
        exit(1);
    }
    
    struct stat buf;
    if(stat(argv[1],&buf) == -1){
        perror("stat");
        exit(1);
    }

    //Create hard link if regular file
    if(S_ISREG(buf.st_mode)){

        if(link(argv[1],"file.hard") == -1){
            perror("link");
            exit(1);
        }
    }
    else{
        printf("[ERROR] No regular file\n");
    }

    return 0;
}
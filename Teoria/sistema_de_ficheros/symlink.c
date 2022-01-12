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

    //Create symlink if regular file
    if(S_ISREG(buf.st_mode)){

        if(symlink(argv[1],"file.sym") == -1){
            perror("symlink");
            exit(1);
        }
        else{
            char *b[7];
            if(readlink("file.sym",b,7) == -1){
                perror("readlink");
                exit(1);
            }
            b[6] = "\0";

            printf("Symlink created referred to %s\n",b);
        }
    }
    else{
        printf("[ERROR] No regular file\n");
    }

    return 0;
}
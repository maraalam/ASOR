#include <stdio.h>
#include <errno.h>
#include <string.h>

//Open
#include <stdlib.h>
#include <fcntl.h>

/*Error handling while trying to open an missing file*/

int main (int argc, char **argv){

    FILE * fp;
    fp = open("file.txt",O_WRONLY);

    if (fp == -1){
        int error = errno;
        char *errorstr = strerror(errno);
        

        //Differents ways to print an error
        
        //perror("open");                         //print -> open: No such file or directory
        perror(errorstr);                         //print -> No such file or directory
        //pritnf("%d:%s\n", error, errorstr);   

        exit(1);
    }

    close(fp);


    return 0;
}
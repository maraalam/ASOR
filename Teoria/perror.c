#include <stdio.h>      //error
#include <errno.h>
#include <string.h>

#include <sys/types.h>  //open
#include <sys/stat.h>
#include <fcntl.h>

/*Error handling while trying to open an missing file*/

int main (int argc, char **argv){

    int * fp = open("file.txt",O_WRONLY);

    if (fp == -1){      

        //Differents ways to print an error
        
        perror("open");  //open: No such file or directory

        char *errorstr = strerror(errno);
        printf("error code %d : %s\n", errno, errorstr);   //Error code 2 : No such file or directory

        exit(1);
    }

    close(fp);


    return 0;
}

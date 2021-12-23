#include <stdio.h>
#include <errno.h>
#include <string.h>

//Open
#include <stdlib.h>
#include <fcntl.h>

/*Error handling while trying to open an missing file*/

int main (int argc, char **argv){

    int * fp = open("file.txt",O_WRONLY);

    if (fp == -1){
        int error = errno;
      

        //Differents ways to print an error
        
        perror("open");  //open: No such file or directory
        
        char *errorstr = strerror(errno);
        printf("Error code %d : %s\n", error, errorstr);   //Error code 2 : No such file or directory

        exit(1);
    }

    close(fp);


    return 0;
}

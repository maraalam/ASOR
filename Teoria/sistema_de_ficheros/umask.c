#include <sys/types.h>  //open & umask
#include <sys/stat.h>
#include <fcntl.h>      //FLAGS open

#include <stdio.h>      //error
#include <errno.h>
#include <string.h>



/*
FLAGS TYPE OPEN
    O_RDONLY -> Only read
    O_WRONLY -> Only write
    0_RDWR   -> Read and Write


OTHERS FLAGS

O_APPEND    -> The text write will be written at the end of the 'file'
O_CREAT     -> If the file doesn't exists, it would be create with mode indicated in 'mode'
O_EXCL      -> With O_CREAT, produces an error if the 'file' exists.
O_TRUNC     -> File is truncated
O_NONBLOCK  -> Open... a 'file' without delay. (This action can't be block by other process)
O_SYNC      -> Blocks write operations until data is physically written to memory


*/

int main(){

    int mask = umask(0132); // --x-wx-w-
    int *fp;

    //create a new file with permissions
    fp = open("file.txt", O_CREAT | O_RDONLY, 0777); // mode & ~mask => rw-r--r-x

    if(fp == -1){
        perror("open");
        exit(1);
    }

    close(fp);


    return 0;
}

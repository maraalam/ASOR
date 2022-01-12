#include <unistd.h>      //pathconf

#include <stdio.h>       //error
#include <errno.h>
#include <string.h>

int main(int argc, char **argv){

    long value;
    int error;

    if((value = pathconf(".",_PC_LINK_MAX)) == -1){
        error = errno;
        perror("pathconf_PC_LINK_MAX");
        exit(1);
    }
    
    printf("_PC_LINK_MAX: %d\n",value);


    if((value = pathconf(".",_PC_NAME_MAX)) == -1){
        error = errno;
        perror("pathconf_PC_NAME_MAX");
        exit(1);
    }
    
    printf("_PC_NAME_MAX: %d\n",value);


    if((value = pathconf(".",_PC_PATH_MAX)) == -1){
        error = errno;
        perror("pathconf_PC_PATH_MAX");
        exit(1);
    }
    
    printf("_PC_PATH_MAX: %d\n",value);

    
    if((value = pathconf(".",_PC_CHOWN_RESTRICTED)) == -1){
        error = errno;
        perror("pathconf_PC_CHOWN_RESTRICTED");
        exit(1);
    }
    
    printf("_PC_CHOWN_RESTRICTED: %d\n",value);


    if((value = pathconf(".",_PC_PIPE_BUF)) == -1){
        error = errno;
        perror("pathconf_PC_PIPE_BUF");
        exit(1);
    }
    
    printf("_PC_PIPE_BUF: %d\n",value);

    return 0;
}

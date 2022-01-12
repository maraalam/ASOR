#include <unistd.h>      //sysconf

#include <stdio.h>       //error
#include <errno.h>
#include <string.h>


int main(int argc,char **argv){

    /*sysconf DON'T SET THE VALUE OF ERRNO*/
    long value;

    if((value = sysconf(_SC_ARG_MAX)) == -1){
        perror("sysconf_SC_ARG_MAX");
        exit(1);
    }
    
    printf("_SC_ARG_MAX: %d\n",value);


    if((value = sysconf(_SC_CLK_TCK)) == -1){
        perror("sysconf_SC_CLK_TCK");
        exit(1);
    }
    
    printf("_SC_CLK_TCK: %d\n",value);


    if((value = sysconf(_SC_OPEN_MAX)) == -1){
        perror("sysconf_SC_OPEN_MAX");
        exit(1);
    }
    
    printf("_SC_OPEN_MAX: %d\n",value);

    
    if((value = sysconf(_SC_PAGESIZE)) == -1){
        perror("sysconf_SC_PAGESIZE");
        exit(1);
    }
    
    printf("_SC_PAGESIZE: %d\n",value);


    if((value = sysconf(_SC_CHILD_MAX)) == -1){
        perror("sysconf_SC_CHILD_MAX");
        exit(1);
    }
    
    printf("_SC_CHILD_MAX: %d\n",value);


    return 0;
}

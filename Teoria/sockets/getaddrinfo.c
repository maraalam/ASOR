#include <stdio.h>      //error
#include <errno.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <stdlib.h>


int main(int argc, char *argv){

    if(argc < 2){
        fprintf(stderr,"[ERROR] Incorrect parameters\n");
        exit(1);
    }

    
    struct addrinfo *res;
    
    if(getaddrinfo(argv[1], NULL, NULL, &res) == -1){
        perror("getaddrinfo");
        exit(1);
    }

    while(res->ai_next != NULL){

        printf("Familia %i\n",res->ai_family);
        printf("Tipo de socket %i\n",res->ai_socktype);


        char *hbuf[NI_MAXHOST];
        getnameinfo(res->ai_addr, INET_ADDRSTRLEN, hbuf, NI_MAXHOST, NULL,NULL, NI_NUMERICHOST);
        
        printf("Direccion %\s\n",hbuf);


        if(res->ai_family == AF_INET){//ipv4
            
            char dir[INET_ADDRSTRLEN];
            struct sockaddr_in *sock = res->ai_addr;
            inet_ntop(AF_INET, &(sock->sin_addr),dir,INET_ADDRSTRLEN);
            printf("IP numerica ipv4: %s\n",dir);

        }
        else if(res->ai_family == AF_INET6){//ipv6
            char dir[INET6_ADDRSTRLEN];
            struct sockaddr_in6 *sock = res->ai_addr;
            inet_ntop(AF_INET6, &(sock->sin6_addr),dir,INET6_ADDRSTRLEN);
            printf("IP numerica ipv4: %s\n",dir);

        }
        
        res = res->ai_next;
        printf("\n");
    }


    return 0;
}
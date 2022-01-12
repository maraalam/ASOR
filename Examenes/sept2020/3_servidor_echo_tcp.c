#include <sys/types.h>          
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <errno.h>




int main(int argc, char *argv[]){


    if (argc < 3 ){
        perror("Numero de parametros incorrecto\n");
        exit(1);
    }

    char *dir = argv[1];
    char *port = argv[2];


    struct addrinfo hints;
    struct addrinfo *result;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_STREAM; /* Datagram socket */
    hints.ai_flags = 0;    

    if(getaddrinfo(dir, port, &hints, &result) == -1){
        perror("getaddrinfo");
        exit(1);
    }



    int sd = socket(result->ai_family, result->ai_socktype, 0);

    bind(sd, result->ai_addr,result->ai_addrlen);

    listen(sd, 100);




    char buf[80];
    char host[NI_MAXHOST];
    char serv[NI_MAXSERV];
    struct sockaddr_storage *addr;
    struct socklen_t *addrlen;

    int client = accept(sd, (struct sokaddr*) &addr, &addrlen);

    while(1){

        int s = getnameinfo((struct sokaddr*) &addr, &addrlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);

        printf("Connect from %s:%s\n",host, serv);

        ssize_t bytes = recv(client, buf, 80, 0);

        buf[bytes] = '\0';

        
        printf("Message from client: %s\n",buf);

        send(client, buf, bytes,0);
   

    }

    close(sd);
    close(client);



    return 0;
}
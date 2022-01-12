#include <sys/types.h>          
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>

/* According to POSIX.1-2001 */
#include <sys/select.h>

/* According to earlier standards */
#include <sys/time.h>
#include <unistd.h>


int main(int argc, char *argv[]){

    if (argc < 3) {
        printf("Numero de parametros incorrecto\n");
        exit(1);
    }


    char *dir = argv[1];
    char *port = argv[2];

    struct addrinfo hints;
    struct addrinfo *result;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
    hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */

    getaddrinfo(dir, port, &hints, &result);


    int server = socket(result->ai_family, result->ai_socktype,0);
    bind(server, result->ai_addr, result->ai_addrlen);


    size_t bytes;
    char buf[255];
    struct sockaddr_storage addr;
    socklen_t addrlen;


    //multiplexacion
    fd_set readfds;
    int rv = -1;

    while(1){

        while(rv == -1){
            FD_ZERO(&readfds);
            FD_SET(0,&readfds);
            FD_SET(server, &readfds);
            rv = select(server+1, &readfds, NULL, NULL, NULL);
        }

        //Message from client
        if(FD_ISSET(server, &readfds)){
            
            bytes = recvfrom(server, buf, 255, 0,(struct sockaddr*) &addr, &addrlen);

            buf[bytes-1] = '\0';

            
            socklen_t len;         /* input */
            char host[NI_MAXHOST];
            char serv[NI_MAXSERV];

            getnameinfo((struct sockaddr*) &addr, &addrlen, host, NI_MAXHOST,
                        serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);

            printf("Connect from %s:%s\n",host,serv);
            printf("Message recv from client: %s\n",buf);

        }
        //Message from terminal
        else if(FD_ISSET(0,&readfds)){
            bytes = read(0,buf,255);
            buf[bytes-1] = '\0';
            printf("Message recv from terminal: %s\n",buf);
        }

        char message_send[255];

        time_t time_ = time(NULL);

        struct tm *local_time = localtime(&time_);
            
        size_t time_bytes = strftime(message_send, 255, "%r",local_time);

        //Message to client
        if(FD_ISSET(server, &readfds)){
            sendto(server,message_send,255, 0, (struct sockaddr *)&addr, addrlen);
            printf("Message send to client: %s\n",message_send);
        }
        //Message from terminal
        else if(FD_ISSET(0,&readfds)){
            printf("Message send to terminal: %s\n",message_send);
        }
        rv = -1;
    }

    close(server);


    return 0;
}

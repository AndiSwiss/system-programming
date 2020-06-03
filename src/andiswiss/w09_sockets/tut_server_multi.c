//
// from https://www.tutorialspoint.com/unix_sockets/socket_quick_guide.htm
//

/**
 * Handle Multiple Connections
 *
 * To allow the server to handle multiple simultaneous connections, we make the following changes in the previous code:
 * - Put the accept statement and the following code in an infinite loop.
 * - After a connection is established, call fork() to create a new process.
 * - The child process will close sockfd and call doProcessing function, passing the new socket file descriptor as an
 *   argument. When the two processes have completed their conversation, as indicated by doProcessing() returning,
 *   this process simply exits.
 * - The parent process closes newsockfd. As all of this code is in an infinite loop, it will return to the accept
 *   statement to wait for the next connection.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>


#define PORT_NO 5001

void doProcessing (int sock);

int main( int argc, char *argv[] ) {
    int sockfd, newsockfd, portno, clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n, pid;

    /* First call to socket() function */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    /* Initialize socket structure */
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = PORT_NO;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    /* Now bind the host address using bind() call.*/
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }

    /* Now start listening for the clients*/
    listen(sockfd,5);
    clilen = sizeof(cli_addr);

    while (1) {
        /* Accept actual connection from the client */
        /* After here, this process will go in sleep mode and will wait for the incoming connection */
        printf("Listening on port %d and ready to accept...\n", portno);
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

        if (newsockfd < 0) {
            perror("ERROR on accept");
            exit(1);
        }

        /* Create child process */
        pid = fork();

        if (pid < 0) {
            perror("ERROR on fork");
            exit(1);
        }

        if (pid == 0) {
            /* This is the client process */
            close(sockfd);
            doProcessing(newsockfd);
            exit(0);
        }
        else {
            close(newsockfd);
        }

    } /* end of while */
}


void doProcessing (int sock) {
    int n;
    char buffer[256];
    bzero(buffer,256);
    n = read(sock,buffer,255);

    if (n < 0) {
        perror("ERROR reading from socket");
        exit(1);
    }

    printf("Here is the message: %s\n",buffer);
    n = write(sock,"I got your message",18);

    if (n < 0) {
        perror("ERROR writing to socket");
        exit(1);
    }
}
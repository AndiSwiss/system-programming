//
// from https://www.tutorialspoint.com/unix_sockets/socket_quick_guide.htm
//
/**
 * To make a process a TCP server, you need to follow the steps given below −
 * - Create a socket with the socket() system call.
 * - Bind the socket to an address using the bind() system call. For a server socket on the Internet, an address
 *   consists of a port number on the host machine.
 * - Listen for connections with the listen() system call.
 * - Accept a connection with the accept() system call. This call typically blocks until a client connects with
 *   the server.
 * - Send and receive data using the read() and write() system calls.
 *
 * Now let us put these steps in the form of source code. Put this code into the file server.c and compile it with
 * gcc compiler.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>


#define PORT_NO 5001


int main(void) {
    int sockfd, newsockfd, portno, clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;

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
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    /* Accept actual connection from the client */
    /* After here, this process will go in sleep mode and will wait for the incoming connection */
    printf("Listening on port %d and ready to accept...\n", portno);
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

    if (newsockfd < 0) {
        perror("ERROR on accept");
        exit(1);
    }

    /* If connection is established then start communicating */
    bzero(buffer, 256);
    n = read(newsockfd, buffer, 255);

    if (n < 0) {
        perror("ERROR reading from socket");
        exit(1);
    }

    printf("Here is the message: %s\n", buffer);

    /* Write a response to the client */
    n = write(newsockfd, "I got your message", 18);

    if (n < 0) {
        perror("ERROR writing to socket");
        exit(1);
    }

    return 0;
}
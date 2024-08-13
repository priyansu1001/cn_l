#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MYPORT 4952 // the port users will be connecting to
#define MAXBUFLEN 200

int main() {
    int sockfd;
    struct sockaddr_in my_addr; // my address information
    struct sockaddr_in their_addr; // connector's address information
    socklen_t addr_len;
    int numbytes;
    char buf[MAXBUFLEN];

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    // Bind socket to port
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(MYPORT);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    memset(my_addr.sin_zero, '\0', sizeof my_addr.sin_zero);

    if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof my_addr) == -1) {
        perror("bind");
        exit(1);
    }

    printf("UDP server waiting for incoming messages on port %d...\n", MYPORT);

    while (1) {
        addr_len = sizeof their_addr;
        
        // Receive message from client
        if ((numbytes = recvfrom(sockfd, buf, MAXBUFLEN-1 , 0,
            (struct sockaddr *)&their_addr, &addr_len)) == -1) {
                perror("recvfrom");
                exit(1);
        }
        buf[numbytes] = '\0';
        printf("Server received message from %s: '%s'\n", inet_ntoa(their_addr.sin_addr), buf);

        // Respond to client
        char response[] = "Message received by server";
        if ((numbytes = sendto(sockfd, response, strlen(response), 0,
            (struct sockaddr *)&their_addr, addr_len)) == -1) {
                perror("sendto");
                exit(1);
        }
        printf("Server sent %d bytes back to %s\n", numbytes, inet_ntoa(their_addr.sin_addr));
    }

    close(sockfd);
    return 0;
}

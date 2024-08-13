#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVERPORT 4952 // the port server is listening on
#define MAXBUFLEN 200
int main() {
    int sockfd;
    struct sockaddr_in their_addr; // server's address information
    int numbytes;
    char arg[30];
    char buf[MAXBUFLEN];

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    their_addr.sin_family = AF_INET; // host byte order
    their_addr.sin_port = htons(SERVERPORT); // short, network byte order
    their_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // localhost IP address
    memset(their_addr.sin_zero, '\0', sizeof their_addr.sin_zero);

    // Send message to server
    printf("Enter a message to send to the server:\n");
    fgets(arg, sizeof(arg), stdin);
    arg[strcspn(arg, "\n")] = '\0'; // Remove newline character from input

    if ((numbytes = sendto(sockfd, arg, strlen(arg), 0,
        (struct sockaddr *)&their_addr, sizeof their_addr)) == -1) {
            perror("sendto");
            exit(1);
    }

    printf("Client sent %d bytes to server\n", numbytes);

    // Receive response from server
    socklen_t addr_len = sizeof their_addr;
    if ((numbytes = recvfrom(sockfd, buf, sizeof(buf)-1, 0,
        (struct sockaddr *)&their_addr, &addr_len)) == -1) {
            perror("recvfrom");
            exit(1);
    }

    buf[numbytes] = '\0';
    printf("Client received response from server: '%s'\n", buf);

    close(sockfd);
    return 0;
}

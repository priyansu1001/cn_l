// dir lis (client will ask for list and server will send back the lis)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUF_SIZE 1024

int main() {
    int sockfd;
    char buffer[BUF_SIZE];
    struct sockaddr_in server_addr;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));

    // Filling server information
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Send request to server
    snprintf(buffer, BUF_SIZE, "LIST");
    sendto(sockfd, buffer, strlen(buffer), 0, (const struct sockaddr *)&server_addr, sizeof(server_addr));
    printf("Client sent LIST request to server\n");

    // Receive response from server
    int n = recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);
    buffer[n] = '\0';
    printf("Client received directory listing from server:\n%s\n", buffer);

    close(sockfd);
    return 0;
}

// write a c program to create a udp socket through which client will send a message to the server and the server will echo back a message to the client. when the client will send exit, both will drop the connection


// udp_server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];
    ssize_t recv_len;

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set up server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind socket
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d\n", PORT);

    while (1) {
        recv_len = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &addr_len);
        if (recv_len < 0) {
            perror("Receive failed");
            break;
        }
        buffer[recv_len] = '\0';
        printf("Received message: %s\n", buffer);

        // Check for "exit" message
        if (strcmp(buffer, "exit") == 0) {
            printf("Exiting server...\n");
            break;
        }

        // Echo the message back to the client
        if (sendto(sockfd, buffer, recv_len, 0, (struct sockaddr *)&client_addr, addr_len) < 0) {
            perror("Send failed");
            break;
        }
    }

    close(sockfd);
    return 0;
}


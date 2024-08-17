// swapping server (2client )
// same as lab3 server 4
// write a program to create a udp socket through which a server will accept a number from client 1 and forward it to client 2, and accept a number from client 2 and send to client 1 (swapping server)

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
    struct sockaddr_in server_addr, client1_addr, client2_addr;
    socklen_t addr_len = sizeof(struct sockaddr_in);
    int num1, num2;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client1_addr, 0, sizeof(client1_addr));
    memset(&client2_addr, 0, sizeof(client2_addr));

    // Filling server information
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Server is running and waiting for clients...\n");

    // Receive number from client 1
    recvfrom(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *)&client1_addr, &addr_len);
    num1 = atoi(buffer);
    printf("Received %d from client 1\n", num1);

    // Receive number from client 2
    recvfrom(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *)&client2_addr, &addr_len);
    num2 = atoi(buffer);
    printf("Received %d from client 2\n", num2);

    // Send client 1's number to client 2
    snprintf(buffer, BUF_SIZE, "%d", num1);
    sendto(sockfd, buffer, BUF_SIZE, 0, (const struct sockaddr *)&client2_addr, addr_len);

    // Send client 2's number to client 1
    snprintf(buffer, BUF_SIZE, "%d", num2);
    sendto(sockfd, buffer, BUF_SIZE, 0, (const struct sockaddr *)&client1_addr, addr_len);

    printf("Numbers swapped and sent to respective clients.\n");

    close(sockfd);
    return 0;
}


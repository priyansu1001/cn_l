// write a program to create a udp socket through which a server will accept a number from client 1 and forward it to client 2, and accept a number from client 2 and send to client 1 (swapping server)


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUF_SIZE 1024

void client_function(int client_num, int num_to_send) {
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

    // Send number to server
    snprintf(buffer, BUF_SIZE, "%d", num_to_send);
    sendto(sockfd, buffer, BUF_SIZE, 0, (const struct sockaddr *)&server_addr, sizeof(server_addr));
    printf("Client %d sent %d to server\n", client_num, num_to_send);

    // Receive swapped number from server
    recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);
    printf("Client %d received %s from server\n", client_num, buffer);

    close(sockfd);
}

int main() {
    int client_num;
    int num_to_send;

    printf("Enter client number (1 or 2): ");
    scanf("%d", &client_num);
    printf("Enter number to send: ");
    scanf("%d", &num_to_send);

    client_function(client_num, num_to_send);

    return 0;
}

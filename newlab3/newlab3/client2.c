//write a c program to create a udp socket through which client will send 2 interger numbers to the server, the server will add these 2 intergers and will send back the result

// udp_client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    socklen_t addr_len = sizeof(server_addr);

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set up server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server IP address
    server_addr.sin_port = htons(PORT);

    while (1) {
        // Get integers from user
        int num1, num2;
        printf("Enter first integer: ");
        scanf("%d", &num1);
        printf("Enter second integer: ");
        scanf("%d", &num2);
        snprintf(buffer, BUFFER_SIZE, "%d %d", num1, num2);

        // Send integers to server
        if (sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&server_addr, addr_len) < 0) {
            perror("Send failed");
            break;
        }

        // Receive result from server
        ssize_t recv_len = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&server_addr, &addr_len);
        if (recv_len < 0) {
            perror("Receive failed");
            break;
        }
        buffer[recv_len] = '\0';
        printf("Server response: The sum is %s\n", buffer);
    }

    close(sockfd);
    return 0;
}


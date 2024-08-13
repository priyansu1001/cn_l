//write a c program to create a udp socket through which client will send 2 interger numbers to the server, the server will add these 2 intergers and will send back the result

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
        // Receive data from client
        recv_len = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &addr_len);
        if (recv_len < 0) {
            perror("Receive failed");
            break;
        }

        buffer[recv_len] = '\0';

		//editing start
        // Parse integers from buffer
        int num1, num2;
        if (sscanf(buffer, "%d %d", &num1, &num2) != 2) {
            fprintf(stderr, "Invalid input from client\n");
            continue;
        }

        // Calculate the sum
        int result = num1 + num2;


        //editing end
        
        // Send result back to client
        snprintf(buffer, BUFFER_SIZE, "%d", result);
        if (sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&client_addr, addr_len) < 0) {
            perror("Send failed");
            break;
        }
    }

    close(sockfd);
    return 0;
}


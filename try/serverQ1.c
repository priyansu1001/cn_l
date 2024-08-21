// server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    int num1, num2, sum;

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Set up the address structure
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the address and port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", PORT);

    // Accept an incoming connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Read the two numbers from the client
    read(new_socket, buffer, BUFFER_SIZE);
    num1 = atoi(buffer);

    read(new_socket, buffer, BUFFER_SIZE);
    num2 = atoi(buffer);

    printf("Received numbers: %d and %d\n", num1, num2);

    // Perform the calculation (sum of the two numbers)
    sum = num1 + num2;

    // Send the result back to the client
    snprintf(buffer, BUFFER_SIZE, "%d", sum);
    send(new_socket, buffer, strlen(buffer), 0);
    printf("Result sent back to client: %d\n", sum);

    // Close the sockets
    close(new_socket);
    close(server_fd);

    return 0;
}


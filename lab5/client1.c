// client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};
    char input[BUFFER_SIZE];

    // Create socket file descriptor
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        return -1;
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection Failed");
        return -1;
    }

    // Read the first number from the user
    printf("Enter the first number: ");
    fgets(input, BUFFER_SIZE, stdin);
    send(sock, input, strlen(input), 0);

    // Read the second number from the user
    printf("Enter the second number: ");
    fgets(input, BUFFER_SIZE, stdin);
    send(sock, input, strlen(input), 0);

    // Receive the result from the server
    read(sock, buffer, BUFFER_SIZE);
    printf("Result from server: %s\n", buffer);

    // Close the socket
    close(sock);

    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 256

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    int roll_number;

    // Create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Define server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(PORT);

    // Connect to the server
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    // Get roll number from user
    printf("Enter roll number: ");
    scanf("%d", &roll_number);

    // Send roll number to server
    snprintf(buffer, sizeof(buffer), "%d", roll_number);
    write(client_socket, buffer, strlen(buffer));

    // Receive and print student details from server
    memset(buffer, 0, sizeof(buffer)); // Clear buffer
    read(client_socket, buffer, sizeof(buffer));
    printf("Student Details: %s\n", buffer);

    close(client_socket);
    return 0;
}


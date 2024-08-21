#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 256

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    FILE *file;
    int roll_number;
    char line[BUFFER_SIZE];

    // Open the file containing student details
    file = fopen("studentDetails.txt", "r");
    if (file == NULL) {
        perror("Could not open file");
        close(client_socket);
        return;
    }

    // Receive roll number from client
    read(client_socket, buffer, sizeof(buffer));
    roll_number = atoi(buffer);

    // Find the student details
    while (fgets(line, sizeof(line), file)) {
        int file_roll_number;
        sscanf(line, "%d", &file_roll_number);
        if (file_roll_number == roll_number) {
            write(client_socket, line, strlen(line));
            fclose(file);
            close(client_socket);
            return;
        }
    }

    // Roll number not found
    write(client_socket, "Student not found", strlen("Student not found"));

    fclose(file);
    close(client_socket);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size = sizeof(client_addr);

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Define server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind socket
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_socket, 5) < 0) {
        perror("Listen failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        // Accept incoming connection
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_size);
        if (client_socket < 0) {
            perror("Client accept failed");
            continue;
        }

        // Handle the client
        handle_client(client_socket);
    }

    close(server_socket);
    return 0;
}


// write a program to create a udp socket through which client will send an integer array to the server, server will sort the array in ascending order and send back the sorted array to the client, and client will display the sorted array



// udp_server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define MAX_ARRAY_SIZE 100

void sort_array(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

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


		// editing start
        // Parse integers from buffer
        int arr[MAX_ARRAY_SIZE];
        int size = 0;
        char *token = strtok(buffer, " ");
        while (token != NULL && size < MAX_ARRAY_SIZE) {
            arr[size++] = atoi(token);
            token = strtok(NULL, " ");
        }

        // Sort the array
        sort_array(arr, size);

        // Prepare sorted array to send back
        snprintf(buffer, BUFFER_SIZE, "%d", arr[0]);
        for (int i = 1; i < size; i++) {
            snprintf(buffer + strlen(buffer), BUFFER_SIZE - strlen(buffer), " %d", arr[i]);
        }


		// editing end
		
		
        // Send result back to client
        if (sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&client_addr, addr_len) < 0) {
            perror("Send failed");
            break;
        }
    }

    close(sockfd);
    return 0;
}


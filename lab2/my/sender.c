#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <receiver_ip> <port> <message>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *receiver_ip = argv[1];
    int port = atoi(argv[2]);
    const char *message = argv[3];
    int sockfd;
    struct sockaddr_in receiver_addr;
    socklen_t receiver_addr_len = sizeof(receiver_addr);
    char buffer[BUFFER_SIZE];
    ssize_t recv_len;

    // Create a UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure the receiver address
    memset(&receiver_addr, 0, sizeof(receiver_addr));
    receiver_addr.sin_family = AF_INET;
    receiver_addr.sin_addr.s_addr = inet_addr(receiver_ip);
    receiver_addr.sin_port = htons(port);

    while (1) {
        // Send a message to the receiver
        if (sendto(sockfd, message, strlen(message), 0, (struct sockaddr *)&receiver_addr, receiver_addr_len) < 0) {
            perror("sendto failed");
            break;
        }

        // Receive response from the receiver
        recv_len = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&receiver_addr, &receiver_addr_len);
        if (recv_len < 0) {
            perror("recvfrom failed");
            break;
        }
        buffer[recv_len] = '\0';
        printf("Received from receiver: %s\n", buffer);

        // Check for "exit" message
        if (strcmp(buffer, "exit") == 0) {
            printf("Exiting...\n");
            break;
        }

        // Wait for the user to input the next message
        printf("Enter message to send: ");
        if (fgets(buffer, BUFFER_SIZE, stdin) != NULL) {
            buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character
            message = buffer;
        }
    }

    close(sockfd);
    return 0;
}


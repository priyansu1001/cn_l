#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    int num = 10; // Number to send to the server
    int result;

    // Create socket file descriptor
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address / Address not supported");
        return -1;
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection Failed");
        return -1;
    }

    // Send integer to the server
    num = htonl(num); // Convert from host byte order to network byte order
    send(sock, &num, sizeof(num), 0);

    // Receive result from the server
    recv(sock, &result, sizeof(result), 0);
    result = ntohl(result); // Convert from network byte order to host byte order

    printf("Result from server: %d\n", result);

    // Close the socket
    close(sock);

    return 0;
}



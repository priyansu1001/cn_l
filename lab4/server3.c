// dir lis (client will ask for list and server will send back the lis)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUF_SIZE 1024

void list_files(char *buffer) {
    struct dirent *de;
    DIR *dr = opendir(".");
    if (dr == NULL) {
        snprintf(buffer, BUF_SIZE, "Could not open current directory");
        return;
    }
    
    strcpy(buffer, "Files:\n");
    while ((de = readdir(dr)) != NULL) {
        strcat(buffer, de->d_name);
        strcat(buffer, "\n");
    }
    closedir(dr);
}

int main() {
    int sockfd;
    char buffer[BUF_SIZE];
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));

    // Filling server information
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Server is running and waiting for client...\n");

    while (1) {
        int n = recvfrom(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *)&client_addr, &addr_len);
        buffer[n] = '\0';
        
        if (strcmp(buffer, "LIST") == 0) {
            printf("Received LIST request from client\n");
            list_files(buffer);
            sendto(sockfd, buffer, strlen(buffer), 0, (const struct sockaddr *)&client_addr, addr_len);
            printf("Sent directory listing to client\n");
        } else {
            printf("Received unknown request from client: %s\n", buffer);
        }
    }

    close(sockfd);
    return 0;
}

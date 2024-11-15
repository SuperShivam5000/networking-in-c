#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    printf("The socket value is: %d\n", sockfd);
    if (sockfd == -1) {
        perror("Socket Creation Failed\n");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server;
    server.sin_port = htons(2000);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    int c = connect(sockfd, (struct sockaddr *)&server, sizeof(server));
    if (c == -1) {
        perror("Connection error\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    } else {
        printf("Successfully connected\n");
    }
    
    while (1) {
        char str[100];

        // Sending message to the server
        printf("Client: ");
        fgets(str, sizeof(str), stdin);
        send(sockfd, &str, sizeof(str), 0);

        // Receiving message from the server
        int bytes_received = recv(sockfd, &str, sizeof(str), 0);
        if (bytes_received > 0) {
            printf("Server: %s\n", str);
        } else if (bytes_received == 0) {
            printf("Server disconnected\n");
            break;
        } else {
            perror("Failed to receive data\n");
            break;
        }
    }

    close(sockfd);
    return 0;
}

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

    int serialno;
    int bytes_received = recv(sockfd, &serialno, sizeof(serialno), 0);
    if (bytes_received > 0) {
        printf("My serial number is: %d\n", serialno);
    } else {
        perror("Failed to receive data\n");
    }

    close(sockfd);
    return 0;
}

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

    struct sockaddr_in server, client;
    server.sin_port = htons(2000);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    int serialno = 0;

    int b = bind(sockfd, (struct sockaddr *)&server, sizeof(server));
    printf("Bind value is: %d\n", b);
    if (b == -1) {
        perror("Bind Failed\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    int l = listen(sockfd, 5);
    if (l == -1) {
        perror("Listen Problem\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    } else {
        printf("Successfully listening to client\n");
    }

    while (1) {
        int size = sizeof(client);
        int clientfd = accept(sockfd, (struct sockaddr *)&client, &size);
        if (clientfd == -1) {
            perror("Failed to connect to client\n");
            continue;  // Continue to accept the next client
        } else {
            printf("Clientfd value is %d\n", clientfd);
            printf("Client IP is: %s\n", inet_ntoa(client.sin_addr));

            send(clientfd, &serialno, sizeof(serialno), 0);
            serialno++;
            close(clientfd);  // Close the client socket after sending data
        }
    }

    close(sockfd);
    return 0;
}

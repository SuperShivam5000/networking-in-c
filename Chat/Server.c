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

            char str[100];
            while (1) {
                // Receiving message from the client
                int bytes_received = recv(clientfd, &str, sizeof(str), 0);
                if (bytes_received > 0) {
                    printf("Client: %s\n", str);
                } else if (bytes_received == 0) {
                    printf("Client disconnected\n");
                    break;
                } else {
                    perror("Failed to receive data\n");
                    break;
                }

                // Sending message to the client
                printf("Server: ");
                fgets(str, sizeof(str), stdin);
                send(clientfd, &str, sizeof(str), 0);
            }
        }
        close(clientfd);  // Close the client socket after communication ends
    }

    close(sockfd);
    return 0;
}

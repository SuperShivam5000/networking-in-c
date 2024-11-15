#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/types.h>

int main() {
    int sockfd;
    struct sockaddr_in server_addr, sender;
    int size = sizeof(sender);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    int b=bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr));
    if (b < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    //LOGIC
    int num1, num2;
    recvfrom(sockfd, &num1, sizeof(int), 0, (struct sockaddr *)&sender, &size);
    recvfrom(sockfd, &num2, sizeof(int), 0, (struct sockaddr *)&sender, &size);
    int sum = num1 + num2;
    sendto(sockfd, &sum, sizeof(int), 0, (const struct sockaddr *)&sender, size);

    close(sockfd);
    return 0;
}

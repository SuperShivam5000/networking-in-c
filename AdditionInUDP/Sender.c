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
    struct sockaddr_in receiver;
    int size = sizeof(receiver);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    receiver.sin_family = AF_INET;
    receiver.sin_port = htons(8080);
    receiver.sin_addr.s_addr = inet_addr("127.0.0.1");

    //LOGIC
    int num1=10; 
    int num2=15;
    sendto(sockfd, &num1, sizeof(int), 0, (const struct sockaddr *)&receiver, size);
    sendto(sockfd, &num2, sizeof(int), 0, (const struct sockaddr *)&receiver, size);
    int sum;
    recvfrom(sockfd, &sum, sizeof(int), 0, (struct sockaddr *)&receiver, &size);
    printf("Sum received: %d\n", sum);

    close(sockfd);
    return 0;
}

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/types.h>

int main(){
    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    printf("The socket value is: %d\n",sockfd);
    if(sockfd==-1) perror("Socket Creation Failed\n");

    struct sockaddr_in server;
    server.sin_port=htons(2000);
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=inet_addr("127.0.0.1");

    int c = connect(sockfd, (struct sockaddr*)&server, sizeof(server));
    if(c==-1)perror("Connection error\n");
    else printf("Successfull connected\n");

    int x = 10, y = 5;
    send(sockfd, &x, sizeof(x), 0);
    send(sockfd, &y, sizeof(y), 0);

    int sum;
    recv(sockfd, &sum, sizeof(sum), 0);
    printf("Data received from server is %d\n", sum);

    close(sockfd);
    return 0;
}
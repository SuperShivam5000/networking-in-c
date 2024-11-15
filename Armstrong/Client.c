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

    int x = 371;
    int armstrong;
    send(sockfd, &x, sizeof(x), 0);

    recv(sockfd, &armstrong, sizeof(armstrong), 0);
    if(armstrong) printf("It is an armstrong number\n");
    else printf("It is not an armstrong number\n");

    close(sockfd);
    return 0;
}
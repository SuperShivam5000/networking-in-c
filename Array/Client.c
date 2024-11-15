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

    int arr[]={1,4,7,4,2,5,8,9,2};
    int min,max,sum,avg;
    send(sockfd,arr,sizeof(arr),0);

    recv(sockfd, &min, sizeof(min), 0);
    recv(sockfd, &max, sizeof(max), 0);
    recv(sockfd, &sum, sizeof(sum), 0);
    recv(sockfd, &avg, sizeof(avg), 0);

    printf("Min: %d\n",min);
    printf("Max: %d\n",max);
    printf("Sum: %d\n",sum);
    printf("Avg: %d\n",avg);

    close(sockfd);
    return 0;
}
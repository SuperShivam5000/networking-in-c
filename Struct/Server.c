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
    struct sockaddr_in server,client;
    server.sin_port=htons(2000);
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=inet_addr("127.0.0.1");
    int b=bind(sockfd,(struct sockaddr*)&server,sizeof(server));
    printf("Bind value is: %d\n",b);
    if(b==-1) perror("Bind Failed\n");
    int l = listen(sockfd,5);
    if(l==-1) perror("Listen Problem\n");
    else printf("Successfully listening to client\n");
    int size = sizeof(client);
    int clientfd = accept(sockfd,(struct sockaddr*)&client,&size);
    if(clientfd==-1) perror("Failed to connect to client\n");
    else printf("Clientfd value is %d\n",clientfd);
    printf("Client ip is: %s\n",inet_ntoa(client.sin_addr));

    struct stud
    {
        int roll;
        char name;
        int m1,m2,m3;
    } stud1;
    recv(clientfd,&stud1,sizeof(struct stud),0);
    int totalmark = stud1.m1+stud1.m2+stud1.m3;
    send(clientfd, &totalmark, sizeof(totalmark), 0);

    close(clientfd);
    close(sockfd);
    return 0;
}
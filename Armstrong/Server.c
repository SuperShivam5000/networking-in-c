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

    int x;
    recv(clientfd, &x, sizeof(x), 0);
    int armstrong,sum=0;
    for(int i=x;i>0;i/=10){
        int r=i%10;
        sum=sum+r*r*r;
    }
    if (sum==x) armstrong=1;
    else armstrong=0;
    send(clientfd, &armstrong, sizeof(armstrong), 0);

    close(clientfd);
    close(sockfd);
    return 0;
}
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

    struct stud
    {
        int roll;
        char name;
        int m1,m2,m3;
    } stud1;
    stud1.roll=526;
    stud1.name='A';
    stud1.m1=78;
    stud1.m2=80;
    stud1.m3=95;
    send(sockfd,&stud1,sizeof(struct stud),0);
    int totalmark;
    recv(sockfd, &totalmark, sizeof(totalmark), 0);
    printf("Name: %c\n", stud1.name);
    printf("Roll: %d\n", stud1.roll);
    printf("M1: %d\n", stud1.m1);
    printf("M2: %d\n", stud1.m2);
    printf("M3: %d\n", stud1.m3);
    printf("Total Marks: %d\n",totalmark);
    

    close(sockfd);
    return 0;
}
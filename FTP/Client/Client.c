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
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    printf("The socket value is: %d\n", sockfd);
    if(sockfd == -1) perror("Socket Creation Failed\n");

    struct sockaddr_in server;
    server.sin_port = htons(2000);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    int c = connect(sockfd, (struct sockaddr*)&server, sizeof(server));
    if(c == -1) perror("Connection error\n");
    else printf("Successfully connected\n");

    // Receive and display the list of files from the server
    char filelist[1024];
    int size1 = recv(sockfd, filelist, sizeof(filelist), 0);
    filelist[size1] = '\0';
    printf("Files available on the server:\n%s\n", filelist);

    // Send the selected file name to the server
    char filename[256];
    printf("Enter the name of the file to download: ");
    scanf("%s", filename);
    send(sockfd, filename, strlen(filename), 0);

    // Receive the file content and save it
    FILE *fp = fopen(filename, "w");
    char buffer[1024];
    int n;
    while((n = recv(sockfd, buffer, sizeof(buffer), 0)) > 0) {
        fwrite(buffer, sizeof(char), n, fp);
    }
    fclose(fp);
    printf("File received and saved as %s\n",filename);

    close(sockfd);
    return 0;
}

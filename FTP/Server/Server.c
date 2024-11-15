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

    struct sockaddr_in server, client;
    server.sin_port = htons(2000);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    int b = bind(sockfd, (struct sockaddr*)&server, sizeof(server));
    printf("Bind value is: %d\n", b);
    if(b == -1) perror("Bind Failed\n");

    int l = listen(sockfd, 5);
    if(l == -1) perror("Listen Problem\n");
    else printf("Successfully listening to client\n");

    socklen_t size = sizeof(client);
    int clientfd = accept(sockfd, (struct sockaddr*)&client, &size);
    if(clientfd == -1) perror("Failed to connect to client\n");
    else printf("Clientfd value is %d\n", clientfd);
    printf("Client ip is: %s\n", inet_ntoa(client.sin_addr));

    // Send the list of files to the client
    system("ls > filelist.txt");
    FILE *fp = fopen("filelist.txt", "r");
    char filelist[1024];
    fread(filelist, sizeof(char), sizeof(filelist), fp);
    fclose(fp);
    send(clientfd, filelist, strlen(filelist), 0);

    // Receive the selected file name from the client
    char filename[256];
    int size1 = recv(clientfd, filename, sizeof(filename), 0);
    filename[size1] = '\0';
    printf("Client requested file: %s\n", filename);

    // Open and send the requested file
    FILE *file_to_send = fopen(filename, "r");
    if(file_to_send == NULL) {
        char error_msg[] = "File not found\n";
        send(clientfd, error_msg, strlen(error_msg), 0);
    } else {
        char buffer[1024];
        int n;
        while((n = fread(buffer, sizeof(char), sizeof(buffer), file_to_send)) > 0) {
            send(clientfd, buffer, n, 0);
        }
        fclose(file_to_send);
        printf("File sent successfully\n");
    }

    close(clientfd);
    close(sockfd);
    return 0;
}

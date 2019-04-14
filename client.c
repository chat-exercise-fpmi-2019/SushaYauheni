 #include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#define MAX 80 
#define PORT 8080 
#define SA struct sockaddr 
#define EXIT_FAILURE 1

void str_cli(FILE *,int );

int main(int argc, char * argv[]) {
    int sock;
    struct sockaddr_in server;
    char buffers[1024];
    char data[1024];

    if (argc != 3) {
        perror("Enter the IP Address and port number of the server!!\n");
        exit(EXIT_FAILURE);
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        printf("FAil to create the Socket\n");
        exit(EXIT_FAILURE);
    }

    bzero( & server, sizeof(server));
    bzero(buffers, 1024);
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[2]));

    if ((inet_pton(AF_INET, argv[1], & server.sin_addr)) <= 0) {
        perror("Ip Address format error\n");
        close(sock);
        exit(EXIT_FAILURE);
    }

    if (connect(sock, (struct sockaddr * ) & server, sizeof(server)) < 0) {
        perror("COnnection Error");
        close(sock);
        exit(EXIT_FAILURE);
    }
    printf("\nEnter the Message to be sent to Server\n");
    str_cli(stdin, sock);
    exit(0);
}

void str_cli(FILE * fp, int sockfd) {
    char buffer[1024];
    bzero(buffer, 1024);

    while (fgets(buffer, 1024, fp) != NULL) {
        send(sockfd, buffer, strlen(buffer), 0);
        bzero(buffer, 1024);
        if (recv(sockfd, buffer, 1024, 0) < 0) {
            perror("\n Client:::Server Terminated permanently\n");
            exit(EXIT_FAILURE);
        } else {
            printf("Received Message from the Server is\n");
            fputs(buffer, stdout);
        }
    }
}


#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <stdio.h>
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#define MAX 80 
#define PORT 8080 
#define SA struct sockaddr 

void str_echo(int);
void ms(FILE * , int);

int main(int argc, char * argv[]) {
    int sock, new_conn;
    struct sockaddr_in server, client;
    int len;

    if (argc != 2) {
        perror("Enter a Port Number!!\n");
        exit(EXIT_FAILURE);
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        printf("Fail to create socket!!");
        exit(EXIT_FAILURE);
    }

    bzero( & server, sizeof(server));
    bzero( & client, sizeof(client));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(atoi(argv[1]));

    if (bind(sock, (struct sockaddr * ) & server, sizeof(server))) {
        perror("Binding Failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

    listen(sock, 5);

    while (1) {
        len = sizeof(client);
        new_conn = accept(sock, (struct sockaddr * ) & client, & len);

        if (new_conn == -1) {
            perror("Acceptance Failed");
            close(sock);
            exit(EXIT_FAILURE);
        }

        str_echo(new_conn);
        close(new_conn);
    }
}

void str_echo(int sockfd) {
    int data_len, i;
    char buffers[1024];

    while (1) {
        bzero(buffers, 1024);
        data_len = recv(sockfd, buffers, 1024, 0);
        if (data_len > 0) {
            if ((i = strcmp(buffers, "bye")) == 0) {
                printf("\nTerminating");
                return;
            } else {
                printf("\n  Message Received from Client is: %s", buffers);
                printf("\nEnter the Message to be sent to the client\n");
                ms(stdin, sockfd);
            }
        } else {}
    }
}

void ms(FILE * fp, int sockfd) {
    char buf[1024];
    bzero(buf, 1024);

    while (fgets(buf, 1024, fp) != NULL) {
        send(sockfd, buf, strlen(buf), 0);
    }
}

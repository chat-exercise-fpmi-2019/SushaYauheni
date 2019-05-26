#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>

#pragma warning(disable: 4996)

int main() {
    int ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in SockAddr;
    SockAddr.sin_family = AF_INET;
    SockAddr.sin_port = htons(1337);
    SockAddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    connect(ClientSocket, (struct sockaddr * ) & SockAddr, sizeof(SockAddr));

    char msg[1024];
    const char usernameMsg[] = "USERNAME MyUName\n";
    costs char passwordMsg[] = "PASSWORD 12345\n";

    send(ClientSocket, & usernameMsg, strlen(usernameMsg), 0); //Send uname
    recv(ClientSocket, & msg, 1024, 0); // Recv pwd request
    send(ClientSocket, & passwordMsg, strlen(passwordMsg), 0); //Send pwd 

    while (1) {
        strcpy(msg, "SEND ");
        scanf("%s", msg + 5); // Destination
        msg[strlen(msg)] = ' ';
        scanf("%s", msg + strlen(msg)); // Msg
        msg[strlen(msg)] = '\n';
        send(ClientSocket, & msg, strlen(msg), 0); // Send msg
        recv(ClientSocket, & msg, 1024, 0); // Recv response
        if (msg[0] == 'M') // Message from user
        {
            msg[strstr(msg, " ")] = ':';
            printf("%s\n", msg);
        } else // Info message
        {
            printf("%s\n", msg + 5);
        }
    }

    return 0;
}

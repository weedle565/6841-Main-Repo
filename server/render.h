#pragma once
#include "microui.h"
#include <SDL.h>

int* get_text_size(const char *text);
void draw_text(const char *text, mu_Vec2 pos, mu_Color colour);
void draw_rect(mu_Rect rect, mu_Color colour);
void draw_icons(int id, mu_Rect rect);
void clean();
void init(int width, int height);
SDL_HitTestResult hit(SDL_Window*, const SDL_Point* area, void* data);
void clear(mu_Color colour);
void present(void);
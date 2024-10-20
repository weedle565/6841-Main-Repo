#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "render.h"

static SDL_Window* window;
static SDL_Renderer* renderer;
static TTF_Font* font;

const SDL_Rect drag_area = {0, 0, 700, 25};

SDL_HitTestResult hit(SDL_Window*, const SDL_Point* area, void* data) {

    if (SDL_PointInRect(area, &drag_area)) {
        return SDL_HITTEST_DRAGGABLE;
    } else {
        return SDL_HITTEST_NORMAL;
    }

}

void init(int width, int height) {
    window = SDL_CreateWindow("Project", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_BORDERLESS);
    renderer = SDL_CreateRenderer(window, -1, 0);
    font = TTF_OpenFont("font.tff", 12);

    SDL_SetWindowHitTest(window, hit, NULL);
}

void clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    TTF_CloseFont(font);
}

void draw_rect(mu_Rect rect, mu_Color colour) {
    SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a);

    SDL_Rect sdlRect = { rect.x, rect.y, rect.w, rect.h};
    SDL_RenderFillRect(renderer, &sdlRect);
}

void draw_text(const char *text, mu_Vec2 pos, mu_Color colour) {

    SDL_Color sdlColour = { colour.r, colour.g, colour.b, colour.a };

}
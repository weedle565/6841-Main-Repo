#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "render.h"

const SDL_Rect drag_area = {0, 0, 700, 25};

SDL_HitTestResult hit(SDL_Window*, const SDL_Point* area, void* data) {

    if (SDL_PointInRect(area, &drag_area)) {
        return SDL_HITTEST_DRAGGABLE;
    }
    return SDL_HITTEST_NORMAL;
}

void init(const int width, const int height) {
    mainWindow = SDL_CreateWindow("Project", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_ALLOW_HIGHDPI);
    renderer = SDL_CreateRenderer(mainWindow, -1, 0);
    font = TTF_OpenFont("font.ttf", 12);

    SDL_SetWindowHitTest(mainWindow, hit, NULL);
}

void clean() {
    SDL_DestroyWindow(mainWindow);
    SDL_DestroyRenderer(renderer);
    TTF_CloseFont(font);
}

void draw_rect(mu_Rect rect, mu_Color colour) {
    SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a);

    SDL_Rect sdlRect = { rect.x, rect.y, rect.w, rect.h};
    SDL_RenderFillRect(renderer, &sdlRect);
}

void draw_text(const char *text, mu_Vec2 pos, mu_Color colour) {
    const SDL_Color sdlColour = { colour.r, colour.g, colour.b, colour.a };
    SDL_Surface* text_surface = TTF_RenderText_Solid(font, text, sdlColour);
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_FreeSurface(text_surface);

    const int text_size[2] = {get_text_size(text)[0], get_text_size(text)[1]};
    const SDL_Rect text_area = { pos.x, pos.y, text_size[0], text_size[1] };
    SDL_RenderCopy(renderer, text_texture, NULL, &text_area);

    SDL_DestroyTexture(text_texture);
}

void draw_icons(const int id, const mu_Rect rect) {

    if (id != 2) return;

    SDL_Surface* image = IMG_Load("assets/icon.png");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);

    SDL_Rect imgRect = {rect.x, rect.y, rect.w, rect.h};

    SDL_RenderCopy(renderer, texture, NULL, &imgRect);

    SDL_DestroyTexture(texture);


}


int* get_text_size(const char *text) {
    static int text_size[2];
    TTF_SizeText(font, text, &text_size[0], &text_size[1]);

    return text_size;
}

void clear(mu_Color colour) {
    SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a);
    SDL_RenderClear(renderer);
}

void present(void) {
    SDL_RenderPresent(renderer);
}
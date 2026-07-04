#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void scc(int code) {
    if (code < 0) {
        fprintf(stderr, "SDL ERROR: %s\n", SDL_GetError());
        exit(1);
    }
    return;
}

void *scp(void *ptr) {
    if (ptr == NULL) {
        fprintf(stderr, "SDL ERROR: %s\n", SDL_GetError());
        exit(1);
    }
    return ptr;
}

SDL_Texture *load_file_as_texture(const char *filepath, SDL_Renderer *renderer) {
    SDL_Surface *surface = scp(IMG_Load(filepath));
    return scp(SDL_CreateTextureFromSurface(renderer, surface));
}

int main(void) {
    scc(SDL_Init(SDL_INIT_EVERYTHING));
    SDL_Window *window = scp(SDL_CreateWindow("Steins Gate", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE));
    SDL_Renderer *renderer = scp(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED));
    SDL_Texture *texture = load_file_as_texture("./charmap-oldschool_white.png", renderer);

    bool quit = false;
    SDL_Event event;
    while (!quit) {
        if (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: {
                    quit = true;
                } break;
            }
        }

        scc(SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF));
        scc(SDL_RenderClear(renderer));

        scc(SDL_RenderCopy(renderer, texture, NULL, &(SDL_Rect) {
                    .x = 0,
                    .y = 0,
                    .w = 128 * 5,
                    .h = 64 * 5
                }));

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

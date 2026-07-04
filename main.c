#define RENDER_IMPLEMENTATION
#include "./render.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600


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

        render_text("Hello, World!", renderer, texture, 5, (Vec2) {0, 0});







        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

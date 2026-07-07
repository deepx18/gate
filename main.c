#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdbool.h>

#include "./render.h"
#include "./buffer.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define BUFFER_CAP 1024
#define FONT_SCALE 2


// char buffer[BUFFER_CAP] = {0};
// size_t buffer_size = 0;
// size_t buffer_cursor = 0;

// [X] TODO: add a cursor
// [X] TODO: move cursor around
// [X] TODO: Remove and insert before and after cursor
// [] TODO: zoom in and out
// [] TODO: add a switch for cursor mode
// [] TODO: multiple lines

int main(void) {
    scc(SDL_Init(SDL_INIT_EVERYTHING));

    char *buffer = malloc(BUFFER_CAP);
    size_t buffer_size = 0;
    size_t buffer_cursor = 0;


    Context ctx = {0};

    SDL_Window *window = scp(SDL_CreateWindow("Steins Gate", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE));

    ctx.scale = FONT_SCALE;
    ctx.renderer = scp(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED));
    ctx.texture = load_file_as_texture(&ctx, "./charmap-oldschool_white.png");

    bool quit = false;
    SDL_Event event;
    while (!quit) {
        if (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: {
                    quit = true;
                } break;

                case SDL_KEYDOWN: {
                    switch (event.key.keysym.sym) {
                        case SDLK_BACKSPACE: {
                            buffer_delete_at(buffer, &buffer_size, &buffer_cursor, 0);
                        } break;

                        case SDLK_DELETE: {
                            buffer_delete_at(buffer, &buffer_size, &buffer_cursor , 1);
                        } break;

                        case SDLK_RIGHT: {
                            if (buffer_cursor < buffer_size) {
                                buffer_cursor += 1;
                            }
                        } break;

                        case SDLK_EQUALS: {
                            if ( event.key.keysym.mod & KMOD_CTRL && event.key.keysym.mod & KMOD_SHIFT) ctx.scale += 1;
                        } break;

                         case SDLK_6: {
                            if ( event.key.keysym.mod & KMOD_CTRL && ctx.scale > 1) ctx.scale -= 1;
                        } break;


                        case SDLK_LEFT: {
                            if (buffer_cursor > 0) buffer_cursor -= 1;
                        } break;

                    }

                } break;

                case SDL_TEXTINPUT: {
                    // printf("%c\n", event.key.keysym.sym);
                    if (!(SDL_GetModState() & KMOD_CTRL))
                        buffer_insert_at(event.text.text, buffer, &buffer_size, &buffer_cursor);
                } break;
            }
        }

        scc(SDL_SetRenderDrawColor(ctx.renderer, 0x00, 0x00, 0x00, 0xFF));
        scc(SDL_RenderClear(ctx.renderer));

        render_text_sized(&ctx, buffer, buffer_size, (Vec2) {0, 0});
        render_cursor(&ctx, buffer, buffer_cursor, buffer_size);
        SDL_RenderPresent(ctx.renderer);
        SDL_Delay(16);
    }


    SDL_DestroyRenderer(ctx.renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

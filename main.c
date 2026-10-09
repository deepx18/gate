#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdbool.h>

#include "./render.h"
#include "./buffer.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define BUFFER_CAP 1024
#define BUFFER_LINES_CAP 10
#define FONT_SCALE 2

Context ctx = {0};
Line lines[BUFFER_LINES_CAP] = {0};

int main(void) {
    scc(SDL_Init(SDL_INIT_EVERYTHING));

    lines[0].items = malloc(BUFFER_CAP);
    lines[0].size = 0;
    lines[0].capacity = BUFFER_CAP;



    SDL_Window *window = scp(SDL_CreateWindow("Steins Gate", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE));

    ctx.scale = FONT_SCALE;
    ctx.renderer = scp(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED));
    ctx.texture = load_file_as_texture(&ctx, "./charmap-oldschool_white.png");
    ctx.cursor = (Vec2) {0, 0};

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
                            buffer_delete_at(&lines[0], (size_t*)&ctx.cursor.x, 0);
                        } break;

                        case SDLK_DELETE: {
                            buffer_delete_at(&lines[0], (size_t*)&ctx.cursor.x , 1);
                        } break;

                        case SDLK_RIGHT: {
                            if (ctx.cursor.x < lines[0].size) {
                                ctx.cursor.x += 1;
                            }
                        } break;

                        case SDLK_EQUALS: {
                            if ( event.key.keysym.mod & KMOD_CTRL && event.key.keysym.mod & KMOD_SHIFT) ctx.scale += 1;
                        } break;

                         case SDLK_6: {
                            if ( event.key.keysym.mod & KMOD_CTRL && ctx.scale > 1) ctx.scale -= 1;
                        } break;


                        case SDLK_LEFT: {
                            if (ctx.cursor.x > 0) ctx.cursor.x -= 1;
                        } break;

                        case SDLK_RETURN: {
                            buffer_insert_newline((Line *)&lines, &ctx);
                        } break;
                    }

                } break;

                case SDL_TEXTINPUT: {
                    // printf("%c\n", event.key.keysym.sym);
                    if (!(SDL_GetModState() & KMOD_CTRL))
                        buffer_insert_at(&lines[0], event.text.text, (size_t *)&(ctx.cursor.x));
                } break;
            }
        }

        scc(SDL_SetRenderDrawColor(ctx.renderer, 0x18, 0x18, 0x18, 0xFF));
        scc(SDL_RenderClear(ctx.renderer));

        render_text_sized(&ctx, lines[0].items, lines[0].size, (Vec2) {0, 0});
        render_cursor(&ctx, lines[0].items, lines[0].size);
        SDL_RenderPresent(ctx.renderer);
        SDL_Delay(16);
    }


    SDL_DestroyRenderer(ctx.renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

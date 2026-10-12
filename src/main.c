#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdbool.h>
#include <time.h>

#include "./render.h"
#include "./buffer.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define BUFFER_CAP 1024
#define FONT_SCALE 2

Context ctx = {0};
Lines buf = {0};

void render_lines(void) {
    for (size_t i = 0; i < buf.count; i++) {
        render_text_sized(&ctx, buf.items[i].items, buf.items[i].size,(Vec2){0, i});
    }
}

int main(void) {

    scc(SDL_Init(SDL_INIT_EVERYTHING));

    buffer_load_file(&buf, __FILE__);

    SDL_Window *window = scp(SDL_CreateWindow("Steins Gate", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE));

    ctx.scale = FONT_SCALE;
    ctx.renderer = scp(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED));
    ctx.texture = load_file_as_texture(&ctx, "./assets/charmap-oldschool_white.png");
    ctx.cursor = (Vec2) {0, 0};

    time_t tracket_time = time(NULL);
    time_t time_diff;
    bool quit = false;
    SDL_Event event;
    while (!quit) {
        if (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: {
                    quit = true;
                } break;

                case SDL_KEYDOWN: {
                    tracket_time = time(NULL);
                    switch (event.key.keysym.sym) {
                        case SDLK_BACKSPACE: {
                            buffer_delete_at(&buf.items[ctx.cursor.y], (size_t*)&ctx.cursor.x, 0);
                        } break;

                        case SDLK_DELETE: {
                            buffer_delete_at(&buf.items[0], (size_t*)&ctx.cursor.x , 1);
                        } break;

                        case SDLK_RIGHT: {
                            if (ctx.cursor.x < buf.items[ctx.cursor.y].size) {
                                ctx.cursor.x += 1;
                            }
                        } break;

                        case SDLK_RETURN: {
                            buffer_insert_newline(&buf, &ctx);
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

                        case SDLK_UP: {
                            if (ctx.cursor.y > 0) {
                                ctx.cursor.y -= 1;
                                if (ctx.cursor.x > buf.items[ctx.cursor.y].size) ctx.cursor.x = buf.items[ctx.cursor.y].size;
                            }
                        } break;

                        case SDLK_DOWN: {
                            if (ctx.cursor.y < buf.count) {
                                ctx.cursor.y += 1;
                                if (ctx.cursor.x > buf.items[ctx.cursor.y].size) ctx.cursor.x = buf.items[ctx.cursor.y].size;
                            }

                        } break;
                    }

                } break;

                case SDL_TEXTINPUT: {
                    // printf("%c\n", event.key.keysym.sym);
                    if (!(SDL_GetModState() & KMOD_CTRL))
                        buffer_insert_at(&buf.items[ctx.cursor.y], event.text.text, (size_t *)&(ctx.cursor.x));
                } break;
            }
        }

        scc(SDL_SetRenderDrawColor(ctx.renderer, 0x18, 0x18, 0x18, 0xFF));
        scc(SDL_RenderClear(ctx.renderer));

        render_lines();

        time_diff = time(NULL) - tracket_time;
        if (time_diff == 0) {
            render_cursor(&ctx, buf.items[ctx.cursor.y].items, buf.items[ctx.cursor.y].size);
        } else if (time_diff >= 2) {
            tracket_time = time(NULL);
            render_cursor(&ctx, buf.items[ctx.cursor.y].items, buf.items[ctx.cursor.y].size);
        }
        SDL_RenderPresent(ctx.renderer);
        SDL_Delay(16);
    }


    SDL_DestroyRenderer(ctx.renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

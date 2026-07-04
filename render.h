#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

#define FONT_CHAR_WIDTH (128 / 18)
#define FONT_CHAR_HEIGHT (64 / 7)

typedef struct {
    int x, y;
}Vec2;

void *scp(void *ptr);
void scc(int code);
SDL_Texture *load_file_as_texture(const char *filepath, SDL_Renderer *renderer);
void render_char(const char *text, SDL_Renderer *renderer, SDL_Texture *texture, int scale, Vec2 pos, size_t idx);
void render_text(const char *text, SDL_Renderer *renderer, SDL_Texture *texture, int scale, Vec2 pos);


#ifndef RENDER_IMPLEMENTATION
#define RENDER_IMPLEMENTATION

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
    SDL_Surface *surface = (SDL_Surface *) scp(IMG_Load(filepath));
    return (SDL_Texture *)scp(SDL_CreateTextureFromSurface(renderer, surface));
}

void render_char(const char *text, SDL_Renderer *renderer, SDL_Texture *texture, int scale, Vec2 pos, size_t idx) {
    (void) pos;
    const size_t chr = text[idx] - 32;
    const int row = floor(chr / 18);
    const int col = (chr % 18);

    scc(SDL_RenderCopy(renderer, texture, &(SDL_Rect) {
                .x = FONT_CHAR_WIDTH * col,
                .y = FONT_CHAR_HEIGHT * row,
                .w = FONT_CHAR_WIDTH,
                .h = FONT_CHAR_HEIGHT
            }, &(SDL_Rect) {
                .x = (int) (FONT_CHAR_WIDTH * idx * scale),
                .y = 0,
                .w = FONT_CHAR_WIDTH * scale,
                .h = FONT_CHAR_HEIGHT * scale
            }));

}

void render_text_sized(const char *text, size_t text_size, SDL_Renderer *renderer, SDL_Texture *texture, int scale, Vec2 pos) {
    for (size_t idx = 0; idx < text_size; idx++) {
        render_char(text, renderer, texture, scale, pos, idx);
    }
}

void render_text(const char *text, SDL_Renderer *renderer, SDL_Texture *texture, int scale, Vec2 pos) {
    render_text_sized(text, strlen(text), renderer, texture, scale, pos);
}


#endif // RENDER_IMPLEMENTATION

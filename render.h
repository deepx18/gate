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
void render_text(const char *text, SDL_Renderer *renderer, SDL_Texture *texture, int scale, Vec2 pos);


#ifdef RENDER_IMPLEMENTATION

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

void render_text(const char *text, SDL_Renderer *renderer, SDL_Texture *texture, int scale, Vec2 pos) {

    for (int c = 0; c < strlen(text); c++) {
        const size_t idx = text[c] - 32;
        const int row = floor(idx / 18);
        const int col = (idx % 18);

        // printf("idx = %zu\nrow = %d\ncol = %d\n", idx, row, col);
        scc(SDL_RenderCopy(renderer, texture, &(SDL_Rect) {
                    .x = FONT_CHAR_WIDTH * col,
                    .y = FONT_CHAR_HEIGHT * row,
                    .w = FONT_CHAR_WIDTH,
                    .h = FONT_CHAR_HEIGHT
                }, &(SDL_Rect) {
                    .x = FONT_CHAR_WIDTH * c * scale,
                    .y = 0,
                    .w = FONT_CHAR_WIDTH * scale,
                    .h = FONT_CHAR_HEIGHT * scale
                }));
    }
}

#endif // RENDER_IMPLEMENTATION

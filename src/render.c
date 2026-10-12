#include <SDL2/SDL_blendmode.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

#include "./render.h"

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


SDL_Texture *load_file_as_texture(Context *ctx, const char *filepath) {
    SDL_Surface *surface = (SDL_Surface *)scp(IMG_Load(filepath));
    Uint32 colorKey = SDL_MapRGB(surface->format, 0x00, 0x00, 0x00);
    SDL_SetColorKey(surface, SDL_TRUE, colorKey);
    return (SDL_Texture *)scp(SDL_CreateTextureFromSurface(ctx->renderer, surface));
}

void set_texture_color(Context *ctx, Uint32 color) {
    scc(SDL_SetTextureColorMod(
            ctx->texture,
            (color >> (8 * 0)) & 0xff,
            (color >> (8 * 1)) & 0xff,
            (color >> (8 * 2)) & 0xff));

    scc(SDL_SetTextureAlphaMod(ctx->texture, (color >> (8 * 3)) & 0xff));
}


void render_char(Context *ctx, const char *text, Vec2 pos, size_t idx) {
    // (void) pos;
    const size_t chr = text[idx] - 32;
    const int row = floor((int)(chr / 18));
    const int col = (chr % 18);

    scc(SDL_RenderCopy(ctx->renderer, ctx->texture, &(SDL_Rect) {
                .x = FONT_CHAR_WIDTH * col,
                .y = FONT_CHAR_HEIGHT * row,
                .w = FONT_CHAR_WIDTH,
                .h = FONT_CHAR_HEIGHT
            }, &(SDL_Rect) {
                .x = (int) (FONT_CHAR_WIDTH * idx * ctx->scale),
                .y = (int) (FONT_CHAR_HEIGHT * pos.y * ctx->scale),
                .w = FONT_CHAR_WIDTH * ctx->scale,
                .h = FONT_CHAR_HEIGHT * ctx->scale
            }));

}

void render_text_sized(Context *ctx, const char *text, size_t text_size, Vec2 pos) {
    set_texture_color(ctx, 0xFFFFFFFF);
    for (size_t idx = 0; idx < text_size; idx++) {
        render_char(ctx, text, pos, idx);
    }
}

void render_text(Context *ctx, const char *text, Vec2 pos) {
    render_text_sized(ctx, text, strlen(text), pos);
}

void render_cursor(Context *ctx, const char *text, size_t bs) {
    SDL_Rect cursor = (SDL_Rect) {
        .x = (int) ctx->cursor.x * FONT_CHAR_WIDTH * ctx->scale,
        .y = (int) ctx->cursor.y * FONT_CHAR_HEIGHT * ctx->scale,
        .w = FONT_CHAR_WIDTH * ctx->scale,
        .h = FONT_CHAR_HEIGHT * ctx->scale
    };

    scc(SDL_SetRenderDrawBlendMode(ctx->renderer, SDL_BLENDMODE_BLEND));
    scc(SDL_SetRenderDrawColor(ctx->renderer, 0xFF, 0xFF, 0xFF, 0xFF));
    scc(SDL_RenderFillRect(ctx->renderer, &cursor));

    set_texture_color(ctx, 0xFF000000);
    if (ctx->cursor.x < strlen(text)) {
        render_char(ctx, text, (Vec2) {ctx->cursor.x, ctx->cursor.y}, ctx->cursor.x);
    }

    return;
}

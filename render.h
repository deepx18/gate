#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <stdlib.h>

#define FONT_CHAR_WIDTH (128 / 18)
#define FONT_CHAR_HEIGHT (64 / 7)

typedef struct {
    int x, y;
} Vec2;

typedef struct {
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    int scale;
} Context;

void *scp(void *ptr);
void scc(int code);
SDL_Texture *load_file_as_texture(Context *ctx, const char *filepath);
void set_texture_color(Context *ctx, Uint32 color);
void render_char(Context *ctx, const char *text, Vec2 pos, size_t idx);
void render_text_sized(Context *ctx, const char *text, size_t text_size, Vec2 pos);
void render_text(Context *ctx, const char *text, Vec2 pos);

void render_cursor(Context *ctx, const char *text, size_t pos, size_t bs);

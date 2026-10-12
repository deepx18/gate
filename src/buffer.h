#ifndef BUFFER_H_
#define BUFFER_H_

#include <sys/types.h>
#include "render.h"

#define BUFFER_LINES_CAP 10

typedef struct {
    size_t capacity;
    size_t size;
    char *items;
} Line;

typedef struct {
    Line *items;
    size_t count;
    size_t capacity;
} Lines;

void buffer_insert_at(Line *line, const char *src, size_t *buffer_cursor);
void buffer_delete_at(Line *line, size_t *buffer_cursor, int offset);
void buffer_insert_newline(Lines *buf, Context *ctx);
void buffer_init(Lines *buf);
void buffer_new_line(Lines *buf);
void buffer_load_file(Lines *buf, const char *file_path);

#endif // BUFFER_H_

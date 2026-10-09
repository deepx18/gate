#ifndef BUFFER_H_
#define BUFFER_H_

#include <sys/types.h>
#include "render.h"

typedef struct {
    size_t capacity;
    size_t size;
    char *items;
} Line;


void buffer_insert_at(Line *line, const char *src, size_t *buffer_cursor);
void buffer_delete_at(Line *line, size_t *buffer_cursor, int offset);
void buffer_insert_newline(Line *lines, Context *ctx);
#endif // BUFFER_H_

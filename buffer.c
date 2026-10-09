#include "./buffer.h"
#include "./render.h"
#include <assert.h>
#include <string.h>

#define BUFFER_CAP 1024

void buffer_insert_at(Line *line, const char *src, size_t *buffer_cursor) {
    const size_t source_len = strlen(src);
    assert( (BUFFER_CAP - line->size) >= source_len );

    if (line->size == *buffer_cursor) {
        memcpy(line->items + (*buffer_cursor), src, source_len);
        line->size += source_len;
        *buffer_cursor = line->size;
    } else {

        const char tmp[BUFFER_CAP] = {0};
        memcpy((char *)tmp, line->items + (*buffer_cursor), line->size - *buffer_cursor);

        memcpy(line->items + (*buffer_cursor), src, source_len);
        memcpy(line->items + (*buffer_cursor) + source_len, tmp, line->size - *buffer_cursor);
        line->size += source_len;
        *buffer_cursor += source_len;
    }

    return;
}

void buffer_delete_at(Line *line, size_t *buffer_cursor, int offset) {

    if (line->size <= 0) return;

    if (line->size == *buffer_cursor) {
        line->size -= 1;
        *buffer_cursor = line->size;
    } else {
        strncpy(line->items + *buffer_cursor - 1 + offset, line->items + *buffer_cursor + offset, line->size - *buffer_cursor);
        line->size -= 1;
        *buffer_cursor -= 1;
        *buffer_cursor += offset;
        memset(line->items + line->size, '\0', BUFFER_CAP);
        // memmove(buffer + *buffer_cursor - 1, buffer + *buffer_cursor, *buffer_size - *buffer_cursor);
    }
    return;
}

void buffer_insert_newline(Line *lines, Context *ctx) {
    (void)lines[ctx->cursor.y].items;
    return;
}

#include "./buffer.h"
#include "./render.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
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

void buffer_insert_newline(Lines *buf, Context *ctx) {
    buffer_new_line(buf);
    ctx->cursor.y += 1;
    ctx->cursor.x =  0;
    return;
}

void buffer_init(Lines *buf) {
    buf->capacity = BUFFER_LINES_CAP;
    buf->count = 0;
    buf->items = malloc(sizeof(Line) * buf->capacity);

    buffer_new_line(buf);
    /* buf->items[1].items = strdup("Hallo, mine friende!!!"); */
    /* buf->items[1].capacity = BUFFER_CAP; */
    /* buf->items[1].size = 22; */
    /* buf->count++; */
}

void buffer_new_line(Lines *buf) {

    assert(buf->count < buf->capacity);
    buf->items[buf->count].items = malloc(BUFFER_CAP);
    buf->items[buf->count].capacity = BUFFER_CAP;
    buf->items[buf->count].size = 0;
    buf->count++;
}


int get_file_length(const char *file_path) {
    FILE *file = fopen(file_path, "r");
    fseek(file, 0, SEEK_END);
    int length = ftell(file);
    fclose(file);
    return length;
}

int count_file_lines(const char *file_path, size_t length) {
    FILE *file = fopen(file_path, "r");
    char buf[length];
    int counter = 0;
    for(;;)
    {
        size_t res = fread(buf, 1, length, file);
        if (ferror(file))
            return -1;

        int i;
        for(i = 0; i < res; i++)
            if (buf[i] == '\n')
                counter++;

        if (feof(file))
            break;
    }
    fclose(file);
    return counter;
}

void buffer_load_file(Lines *buf, const char *file_path) {

#define MAX_LINE_LEN 1024

    int length = get_file_length(file_path);
    int lines_count = count_file_lines(file_path, length);

    FILE *file = fopen(file_path, "r");

    /* char *file_buf = malloc(sizeof(char) * length + 1); */
    /* memset(file_buf, '\0', length + 1); */
    /* fread(file_buf, sizeof(char), length, file); */
    // printf("%s\n", file_buf);

    char line_buf[MAX_LINE_LEN];
    int line = 0;

    printf("%d\n", lines_count);
    buf->capacity = lines_count;
    buf->items = malloc(sizeof(Line) * buf->capacity);
    buf->count = 0;

    while(fgets( line_buf, MAX_LINE_LEN, file)) {

        buf->items[buf->count].items = malloc(MAX_LINE_LEN);
        buf->items[buf->count].capacity = MAX_LINE_LEN;
        buf->items[buf->count].size = strlen(line_buf) - 1;

        memcpy( buf->items[buf->count].items, line_buf, MAX_LINE_LEN);
        buf->count++;

    }

    fclose(file);
    // free(file_buf);
    // (void)buf;
    return;
}

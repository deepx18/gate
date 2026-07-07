#include "./buffer.h"
#include <assert.h>
#include <string.h>


// char buffer[BUFFER_CAP] = {0};
// size_t buffer_size = 0;
// size_t buffer_cursor = 0;

#define BUFFER_CAP 1024


void buffer_insert_at(const char *src, char *buffer, size_t *buffer_size, size_t *buffer_cursor) {
    const size_t source_len = strlen(src);
    assert( (BUFFER_CAP - *buffer_size) >= source_len );

    if (*buffer_size == *buffer_cursor) {
        memcpy(buffer + (*buffer_cursor), src, source_len);
        *buffer_size += source_len;
        *buffer_cursor = *buffer_size;
    } else {

        const char tmp[BUFFER_CAP] = {0};
        memcpy((char *)tmp, buffer + (*buffer_cursor), *buffer_size - *buffer_cursor);

        memcpy(buffer + (*buffer_cursor), src, source_len);
        memcpy(buffer + (*buffer_cursor) + source_len, tmp, *buffer_size - *buffer_cursor);
        *buffer_size += source_len;
        *buffer_cursor += source_len;
    }

    return;
}

void buffer_delete_at(char *buffer, size_t *buffer_size, size_t *buffer_cursor, int offset) {

    if (*buffer_size <= 0) return;

    if (*buffer_size == *buffer_cursor) {
        *buffer_size -= 1;
        *buffer_cursor = *buffer_size;
    } else {
        strncpy(buffer + *buffer_cursor - 1 + offset, buffer + *buffer_cursor + offset, *buffer_size - *buffer_cursor);
        *buffer_size -= 1;
        *buffer_cursor -= 1;
        *buffer_cursor += offset;
        memset(buffer + *buffer_size, '\0', BUFFER_CAP);
        // memmove(buffer + *buffer_cursor - 1, buffer + *buffer_cursor, *buffer_size - *buffer_cursor);
    }
    return;
}

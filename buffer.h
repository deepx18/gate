#include <sys/types.h>


typedef struct {
    int capacity;
    int size;
    char *items;
} Line;

void buffer_insert_at(const char *src, char *buffer, size_t *buffer_size, size_t *buffer_cursor);
void buffer_delete_at(char *buffer, size_t *buffer_size, size_t *buffer_cursor, int offset);

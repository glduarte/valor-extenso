#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>


#define DEFAULT_INIT_SIZE 16

typedef struct Mutable_String {
    char *buf;
    size_t len;
    size_t cap;
} Mutable_String;

int mstr_init(Mutable_String *s);
void mstr_destroy(Mutable_String *s);

int mstr_append(Mutable_String *s, const char *src);

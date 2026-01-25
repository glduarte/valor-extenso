#include "mutable_string.h"
#include <stdlib.h>
#include <string.h>

int mstr_init(Mutable_String *s){
    s->len = 0;
    s->cap = DEFAULT_INIT_SIZE;
    s->buf = malloc(s->cap);

    if (s->buf == NULL) return -1;

    s->buf[0] = '\0';

    return 0;
}

void mstr_destroy(Mutable_String *s) {
    if(s->buf != NULL) {
	free(s->buf);
	s->buf = NULL;
    }

    s->len = 0;
    s->cap = 0;
}

int mstr_append(Mutable_String *s, const char *src) {
    if (s == NULL || src == NULL) return -1;

    size_t src_size = strlen(src);
    size_t mem_needed = s->len + src_size + 1;

    if (mem_needed > s->cap) {
	size_t new_cap = s->cap;

	while(mem_needed > new_cap) new_cap *= 2;

	char *tmp = realloc(s->buf, new_cap);
	if (tmp == NULL) return -1;

	s->buf = tmp;
	s->cap = new_cap;
    }

    memcpy(s->buf + s->len, src, src_size);
    s->len += src_size;
    s->buf[s->len] = '\0';

    return 0;
}

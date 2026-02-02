#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "words_to_value.h"

#define LIT_SIZE(x) (sizeof(x) - 1)

int is_delimiter(char c, const char *delimiters, size_t delimiters_size) {
  for (size_t i = 0; i < delimiters_size; i++) {
    if (c == delimiters[i])
      return 1;
  }

  return 0;
}

size_t chop_buffer(char *buf, size_t buf_size, const char *delimiters,
                   size_t delimiters_size, char **tokens_addresses,
                   size_t max_tokens) {
  size_t i = 0;
  size_t token_i = 0;

  while (i < buf_size) {
    while (i < buf_size && is_delimiter(buf[i], delimiters, delimiters_size))
      i++;

    if (i >= buf_size || token_i >= max_tokens)
      return token_i;

    tokens_addresses[token_i++] = &buf[i];

    while (i < buf_size && !is_delimiter(buf[i], delimiters, delimiters_size))
      i++;

    if (i >= buf_size)
      return token_i;

    buf[i++] = '\0';
  }

  return token_i;
}

int compare_suffix(const char *str, const char *suf) {
  size_t str_size = strlen(str);
  size_t suf_size = strlen(suf);
  if (str_size < suf_size)
    return 0;
  else if (strcmp(str + (str_size - suf_size), suf) == 0)
    return 1;
  return 0;
}

void normalize_str(char *str) {
  size_t i = 0;
  while (str[i] != '\0') {
    if (str[i] >= 'A' && str[i] <= 'Z')
      str[i] += ('a' - 'A');
    i++;
  }

  if (strcmp(str, "cento") == 0) {
    memcpy(str, "cem\0", sizeof("cem"));
  }

  else if (compare_suffix(str, "ões")) {
    memcpy(str + (i - LIT_SIZE("ões")), "ão\0", sizeof("ões"));
  }
}

int main() {
  char str[] = "Três milhões, cento e trinta e quatro";
  size_t str_size = strlen(str) + 1;

  char *tokens_addresses[DEFAULT_MAX_TOKENS] = {0};

  size_t tokens_size = chop_buffer(str, str_size, delimiters, DELIMITERS_SIZE,
                                   tokens_addresses, DEFAULT_MAX_TOKENS);

  for (size_t i = 0; i < tokens_size; i++) {
    normalize_str(tokens_addresses[i]);
  }

  for (size_t j = 0; j < tokens_size; j++) {
    printf("%s\n", tokens_addresses[j]);
  }

  return EXIT_SUCCESS;
}


#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "vw.h"

uint8_t count_digits(uint64_t v) {
  uint8_t c = 0;
  while (v > 0) {
    v = v / 10;
    c++;
  }
  return c;
}

uint8_t has_connective(char *s) {
  size_t i = 1;
  while (s[i] != '\0') {
    if (s[i] == 'e' && s[i - 1] == ' ' && s[i + 1] == ' ')
      return 1;
    i++;
  }
  return 0;
}

char *convert_block(int block) {
  if (block == 0)
    return NULL;

  char *s = (char *)malloc(sizeof(char) * 256);
  if (s == NULL)
    return NULL;

  s[0] = '\0';

  if (block == 100) {
    strcat(s, "cem");
    return s;
  }


  int hundred = block / 100;
  int rest = block % 100;

  if (hundred > 0) {
    strcat(s, hundreds[hundred]);
  }

  if (rest == 0)
    return s;
  else if (rest >= 1 && rest <= 19) {
    if (hundred > 0)
      strcat(s, " e ");
    strcat(s, units[rest]);
  } else {
    int dozen = rest / 10;
    int unit = rest % 10;

    if (hundred > 0)
      strcat(s, " e ");
    strcat(s, dozens[dozen]);

    if (unit > 0)
      strcat(s, " e ");
    strcat(s, units[unit]);
  }

  return s;
}

void join_blocks(char **blocks, size_t blocks_size, uint8_t is_negative,
                  char *dest) {
  size_t j = blocks_size;
  do {
    j--;
    if (j < (blocks_size - 1)) {
      strcat(dest, (j == 0 && (has_connective(blocks[j]) == 0) ? " e " : ", "));
    }
    if (j == (blocks_size - 1)) {
      if (is_negative == 1)
        strcat(dest, "Menos ");
      else
        blocks[j][0] -= 32;
    };

    strcat(dest, blocks[j]);

  } while (j > 0);

  strcat(dest, "\0");
}

char *value_into_words(int64_t v) {
  char *final_str = (char *)malloc(sizeof(char) * 512);
  if (final_str == NULL)
    return NULL;

  final_str[0] = '\0';

  uint8_t is_negative = 0;

  if (v < 0) {
    v = v * -1;
    is_negative = 1;
  }

  if (v == 0) {
    strcpy(final_str, "Zero");
    return final_str;
  }

  uint8_t digits = count_digits(v);

  // mUCQdUXHRUeP
  size_t blocks_quantity = (digits + 2) / 3;

  char **blocks = (char **)malloc(blocks_quantity * sizeof(char *));
  int8_t bi = 0;

  for (size_t i = 0; i < blocks_quantity; i++) {
    uint16_t block = v % 1000;
    v = v / 1000;
    char *s = malloc(1);
    if (block != 1 || i != 1) {
	s = convert_block(block);
	if (s == NULL)
	    continue;

	if (i > 0) {
	    strcat(s, " ");
	}
    }

    if (block > 1)
      strcat(s, plural_scales[i]);
    else
      strcat(s, scales[i]);

    blocks[bi] = s;
    bi++;
  }

  join_blocks(blocks, bi, is_negative, final_str);

  return final_str;
}


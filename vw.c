#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vw.h"
#include "mutable_string.h"

static uint8_t count_digits(uint64_t v) {
    if (v == 0) return 1;

    uint8_t c = 0;
    while (v > 0) {
	v = v / 10;
	c++;
    }
    return c;
}

static uint8_t has_connective(char *s) {
  size_t i = 1;
  while (s[i] != '\0') {
    if (s[i] == 'e' && s[i - 1] == ' ' && s[i + 1] == ' ')
      return 1;
    i++;
  }
  return 0;
}

static int convert_block(int block, Mutable_String *out) {
  if (block == 0)
    return 0;

  if (block == 100) {
    mstr_append(out, "cem");
    return 0;
  }

  int hundred = block / 100;
  int rest = block % 100;

  if (hundred > 0) {
      mstr_append(out, hundreds[hundred]);
  }

  if (rest == 0)
    return 0;
  else if (rest >= 1 && rest <= 19) {
    if (hundred > 0) mstr_append(out, " e ");
    mstr_append(out, units[rest]);
  } else {
    int dozen = rest / 10;
    int unit = rest % 10;

    if (hundred > 0)
      mstr_append(out, " e ");
    mstr_append(out, dozens[dozen]);

    if (unit > 0)
      mstr_append(out, " e ");
    mstr_append(out, units[unit]);
  }

  return 0;
}

static int join_blocks(char **blocks, size_t blocks_size, uint8_t is_negative,
                  Mutable_String *out) {
  size_t j = blocks_size;
  do {
    j--;
    if (j < (blocks_size - 1)) {
	mstr_append(out, (j == 0 && (has_connective(blocks[j]) == 0) ? " e " : ", "));
    }
    if (j == (blocks_size - 1)) {
      if (is_negative == 1)
	mstr_append(out, "Menos ");
      else
        blocks[j][0] -= 32;
    };

    mstr_append(out, blocks[j]);
  } while (j > 0);
  
  return 0;
}

void free_blocks(char **blocks, size_t blocks_size) {
    for (size_t i = 0; i < blocks_size; i++) {
	free(blocks[i]);
    }
    free(blocks);
}

char *value_into_words(int64_t v) {
  int status_code = 0;

  Mutable_String mstr;
  status_code = mstr_init(&mstr);
  if (status_code == -1) return NULL;

  uint8_t is_negative = 0;

  if (v < 0) {
    v = v * -1;
    is_negative = 1;
  }

  if (v == 0) {
      mstr_append(&mstr, "Zero");
      return mstr.buf;
  }

  uint8_t digits = count_digits(v);

  // mUCQdUXHRUeP
  size_t blocks_quantity = (digits + 2) / 3;

  char **blocks = calloc(blocks_quantity, sizeof(char *));
  if (blocks == NULL) { 
      mstr_destroy(&mstr);
      return NULL;
  }

  size_t bi = 0;

  for (size_t i = 0; i < blocks_quantity; i++) {
    uint16_t block = v % 1000;
    v = v / 1000;
    Mutable_String s;
    status_code = mstr_init(&s);
    if (status_code == -1) {
	mstr_destroy(&mstr);
	free_blocks(blocks, bi);
	return NULL;
    }
    if (block != 1 || i != 1) {
      convert_block(block, &s);

      if (block == 0) {
	  mstr_destroy(&s);
	  continue;
      }

      if (i > 0) {
	  mstr_append(&s, " ");
      }
    }

    if (block > 1)
	mstr_append(&s, plural_scales[i]);
    else
	mstr_append(&s, scales[i]);

    blocks[bi] = s.buf;
    bi++;
  }

  join_blocks(blocks, bi, is_negative, &mstr);

  free_blocks(blocks, bi);

  return mstr.buf;
}

#include <stdio.h>
#include <stdlib.h>

#include "vw.h"

int main() {
  char *ans[12] = {};

  ans[0] =  value_into_words(0);
  ans[1] = value_into_words(10);
  ans[2] = value_into_words(15);
  ans[3] = value_into_words(100);
  ans[4] = value_into_words(1000);
  ans[5] = value_into_words(10000000);
  ans[6] = value_into_words(100000000);
  ans[7] = value_into_words(123456789);
  ans[8] = value_into_words(123456015);
  ans[9] = value_into_words(1000000000);
  ans[10] = value_into_words(10000000000);
  ans[11] = value_into_words(100000000000);

  for(size_t i = 0; i < 12; i++) {
      printf("%s\n", ans[i]);
      free(ans[i]);
  }

  return EXIT_SUCCESS;
}

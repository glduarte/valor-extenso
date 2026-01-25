#include <stdio.h>
#include <stdlib.h>

#include "vw.h"

int main() {
  printf("%s\n", value_into_words(0));
  printf("%s\n", value_into_words(10));
  printf("%s\n", value_into_words(15));
  printf("%s\n", value_into_words(100));
  printf("%s\n", value_into_words(1000));
  printf("%s\n", value_into_words(5500));
  printf("%s\n", value_into_words(10000));
  printf("%s\n", value_into_words(100000));
  printf("%s\n", value_into_words(1000000));
  printf("%s\n", value_into_words(10000000));
  printf("%s\n", value_into_words(100000000));
  printf("%s\n", value_into_words(123456789));
  printf("%s\n", value_into_words(123456015));
  printf("%s\n", value_into_words(1000000000));
  printf("%s\n", value_into_words(10000000000));
  printf("%s\n", value_into_words(100000000000));
  return EXIT_SUCCESS;
}

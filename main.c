#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const static char *units[20] = {
    "",       "um",        "dois",      "três",    "quatro",
    "cinco",  "seis",      "sete",      "oito",    "nove",
    "dez",    "onze",      "doze",      "treze",   "quatorze",
    "quinze", "dezesseis", "dezessete", "dezoito", "dezenove"};

const static char *dozens[10] = {"",         "",          "vinte",    "trinta",
                                 "quarenta", "cinquenta", "sessenta", "setenta",
                                 "oitenta",  "noventa"};

const static char *hundreds[10] = {
    "",           "cento",      "duzentos",   "trezentos",  "quatrocentos",
    "quinhentos", "seiscentos", "setecentos", "oitocentos", "novecentos"};


const static char *scales[4] = {"", "mil", "milhão", "bilhão"};

int count_digits(int v) {
  int c = 0;
  while (v > 0) {
    v = v / 10;
    c++;
  }
  return c;
}

char *convert_block(int block) {
  if (block == 0)
    return NULL;
  else if (block == 100)
    return "cem";

  char *s = (char *)malloc(sizeof(char) * 256);
  if (s == NULL)
    return NULL;

  s[0] = '\0';

  int hundred = block / 100;
  int rest = block % 100;

  if (hundred > 0) {
    strcat(s, hundreds[hundred]);
  }

  if (rest == 0)
    return s;
  else if (rest >= 1 && rest <= 19) {
    if (hundred > 0) strcat(s, " e ");
    strcat(s, units[rest]);
  } else {
    int dozen = rest / 10;
    int unit = rest % 10;

    if (hundred > 0) strcat(s, " e ");
    strcat(s, dozens[dozen]);

    if (unit > 0) strcat(s, " e ");
    strcat(s, units[unit]);
  }

  return s;
}

int main() {
  int input = 81234114;

  int digits = count_digits(input);

  for (int i = 0; i < (digits + 2) / 3; i++) {
    char *s = convert_block(input % 1000);
    input = input / 1000;
    if (i > 0) {
	strcat(s, " ");
    }
    strcat(s, scales[i]);
    printf("%s\n", s);
  }

  return EXIT_SUCCESS;
}

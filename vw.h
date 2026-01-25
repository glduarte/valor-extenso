#include <stdint.h>

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

const static char *plural_scales[4] = {"", "mil", "milhões", "bilhões"};


char *value_into_words(int64_t v);

CC = clang
CFLAGS = -std=c99 -g -Werror -Wall -Wextra
FILES = main.c vw.c mutable_string.c
TARGET = vw

main:
	$(CC) $(CFLAGS) $(FILES) -o $(TARGET).out 

test:
	$(CC) $(CFLAGS) words_to_value.c

CC = clang
CFLAGS = -g -Werror -Wall -Wextra
FILES = main.c vw.c mutable_string.c
TARGET = vw

main:
	$(CC) $(CFLAGS) $(FILES) -o $(TARGET).out 

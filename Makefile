CC = clang
CFLAGS = -g -Werror -Wall -Wextra
TARGET = vw

main:
	$(CC) $(CFLAGS) main.c vw.c -o $(TARGET).out 

CC = gcc

CFLAGS = -Wall -Wextra -Iinclude

SRC = src/main.c \
      src/executor.c \
      src/builtins.c \
      src/builtin_handler.c \
      src/input_parser.c

OUT = myshell

all:
	$(CC) $(SRC) $(CFLAGS) -o $(OUT)

clean:
	rm -f $(OUT)
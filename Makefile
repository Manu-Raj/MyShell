CC = gcc

CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS = -lreadline -lncurses

SRC = src/main.c \
      src/executor.c \
      src/builtins.c \
      src/builtin_handler.c \
      src/input_parser.c

OUT = myshell

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(SRC) $(CFLAGS) $(LDFLAGS) -o $(OUT)

clean:
	rm -f $(OUT)
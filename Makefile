CC = gcc
CFLAGS = -Wall -I./gui -I./help -I./matrix -I./variables -I./cli

SRC = main.c \
      gui/gui.c \
      help/help.c \
      matrix/matrix.c \
      variables/variables.c \
      cli/cli.c

OBJ = $(SRC:.c=.o)

EXEC = macierze

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(EXEC) $(OBJ)

CC = gcc
CFLAGS = -Wall -I./gui -I./help -I./matrix -I./variables

SRC = main.c \
      gui/gui.c \
      help/help.c \
      matrix/matrix.c \
      variables/variables.c

OBJ = $(SRC:.c=.o)

EXEC = macierze

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(EXEC) $(OBJ)

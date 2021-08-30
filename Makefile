EXEC = flexfloppy
CC = gcc
CFLAGS   = -std=gnu11 -O3 -Wall -Wextra -Wpedantic -Wstrict-aliasing
LDFLAGS  =

SRC      = $(wildcard *.c)
OBJ      = $(SRC:.c=.o)

all: $(EXEC)

${EXEC}: $(OBJ)
		$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
		$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
		@rm -f *.o

mrproper: clean
		@rm -f $(EXEC)

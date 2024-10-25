CC = gcc
CFLAGS = -Wall -Wextra -std=c99
DEPS1 = q1.h
DEPS2 = q2.h
OBJ1 = q1.o q1_functions.o
OBJ2 = q2.o q2_functions.o

all: q1 q2

%.o: %.c $(DEPS1) $(DEPS2)
    $(CC) -c -o $@ $< $(CFLAGS)

q1: $(OBJ1)
    $(CC) -o $@ $^ $(CFLAGS)

q2: $(OBJ2)
    $(CC) -o $@ $^ $(CFLAGS)

clean:
    rm -f *.o q1 q2

.PHONY: all clean
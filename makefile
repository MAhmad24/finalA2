.RECIPEPREFIX := >

CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: q1 q2

q1: q1.o q1_functions.o
> $(CC) $(CFLAGS) -o q1 q1.o q1_functions.o

q2: q2.o q2_functions.o
> $(CC) $(CFLAGS) -o q2 q2.o q2_functions.o

q1.o: q1.c q1.h
> $(CC) $(CFLAGS) -c q1.c

q1_functions.o: q1_functions.c q1.h
> $(CC) $(CFLAGS) -c q1_functions.c

q2.o: q2.c q2.h
> $(CC) $(CFLAGS) -c q2.c

q2_functions.o: q2_functions.c q2.h
> $(CC) $(CFLAGS) -c q2_functions.c

clean:
> rm -f *.o q1 q2

.PHONY: all clean
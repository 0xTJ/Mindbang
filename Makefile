CFLAGS = -g -Wall

# Should be equivalent to your list of C files, if you don't build selectively
SRC=$(wildcard *.c)

all: $(SRC)
	gcc -o demo $(CFLAGS) $(SRC)
 

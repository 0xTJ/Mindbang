all: demo.c 
	gcc -g -Wall -O0 -o demo demo.c mindbang.c

clean: 
	$(RM) demo

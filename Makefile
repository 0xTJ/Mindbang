all: demo.c 
	gcc -g -Wall -O0 -o demo.exe demo.c mindbang.c

clean: 
	$(RM) demo.exe
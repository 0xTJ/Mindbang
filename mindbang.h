#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char *pTape;
	char *pProg;
} Mindbang;

Mindbang *newMindbang(char* pProg, long lTapeSize);
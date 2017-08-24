#include "mindbang.h"

Mindbang *newMindbang(char* pProg, long lTapeSize) {
	Mindbang *pMb = { malloc(lTapeSize * sizeof(char)), pProg };
	return pMb;
}
/*
void pInc() {
	++tape;
}

void pDec() {
	++tape;
}

void dInc() {
	++*tape;
}

void dDec() {
	--*tape;
}
void dPut() {
	putchar(*tape);
}

void dGet() {
	*tape=getchar();
}

void conWhlB() {
	if (!*tape) {
		int cBr = 1;
		do {
			prog++;
			if (*prog == '[') cBr++;
			else if (*prog == ']') cBr--;
		} while ( cBr != 0 );
		prog++;
	}
}

void conWhlB() {
	if (*tape) {
		int cBr = 1;
		do {
			prog--;
			if (*prog == '[')
				cBr++;
			else if (*prog == ']')
				cBr--;
		} while ( cBr != 0 );
	}
}*/
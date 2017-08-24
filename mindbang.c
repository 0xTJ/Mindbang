#include "mindbang.h"

classMindbang *classMindbang_new(char* pProg, long lTapeSize) {
	int i;
	classMindbang *pMb = &(classMindbang) { NULL, NULL };
	pMb->pProg = pProg;
	pMb->pTape = (char*)malloc(lTapeSize * sizeof(char));
	for (i = 0; i < lTapeSize; i++) {
		pMb->pTape[i] = 0;
	}
	for (i = 0; i < 13; i++)
		putchar(pProg[i]);
	return pMb;
}

void classMindbang_pInc(classMindbang *this) {
	++this->pTape;
}

void classMindbang_pDec(classMindbang *this) {
	++this->pTape;
}

void classMindbang_dInc(classMindbang *this) {
	++*this->pTape;
}

void classMindbang_dDec(classMindbang *this) {
	--*this->pTape;
}
void classMindbang_dPut(classMindbang *this) {
	printf("PUTTING: %c aka %d\n", *this->pTape, *this->pTape);
	putchar(*this->pTape);
}

void classMindbang_dGet(classMindbang *this) {
	*this->pTape=getchar();
}

void classMindbang_whlB(classMindbang *this) {
	if (!*this->pTape) {
		int cBr = 1;
		do {
			this->pProg++;
			if (*this->pProg == '[') cBr++;
			else if (*this->pProg == ']') cBr--;
		} while ( cBr != 0 );
		this->pProg++;
	}
}

void classMindbang_whlE(classMindbang *this) {
	if (*this->pTape) {
		int cBr = 1;
		do {
			this->pProg--;
			if (*this->pProg == '[')
				cBr++;
			else if (*this->pProg == ']')
				cBr--;
		} while ( cBr != 0 );
		++this->pProg;
	}
}

void classMindbang_eval(classMindbang *this) {
	int i;
	char* newPoint = this->pProg;
	this->pProg = newPoint;
	printf("\nnewPoint=%d; this->pProg=%d\n", (int)newPoint, (int)this->pProg);
	for (i = 0; i < 13; i++){
		putchar(*(newPoint + i));
	}
	printf("\nStarting at %d\n", (int)this->pProg);
	printf("Starting at %d\n", (int)this->pProg);
    while (*this->pProg) {
		switch (*this->pProg) {
		case '>':
			classMindbang_pInc(this);
			break;
		case '<':
			classMindbang_pDec(this);
			break;
		case '+':
			classMindbang_dInc(this);
			break;
		case '-':
			classMindbang_dDec(this);
			break;
		case '.':
			classMindbang_dPut(this);
			break;
		case ',':
			classMindbang_dGet(this);
			break;
		case '[':
			classMindbang_whlB(this);
			break;
		case ']':
			classMindbang_whlE(this);
			break;
		}
		(this->pProg)++;
	}
	printf("Ending at %d\n", (int)&this->pProg);
	printf("Ending at %d\n", (int)&this->pProg);
	printf("Ending at %d\n", (int)&this->pProg);
	printf("Ending at %d\n", (int)&this->pProg);
}
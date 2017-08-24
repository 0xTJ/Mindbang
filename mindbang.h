#ifndef MINDBANG_H
#define MINDBANG_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char *pTape;
	char *pProg;
} classMindbang;

classMindbang *classMindbang_new(char* pProg, long lTapeSize);
void classMindbang_pInc(classMindbang *this);
void classMindbang_pDec(classMindbang *this);
void classMindbang_dInc(classMindbang *this);
void classMindbang_dDec(classMindbang *this);
void classMindbang_dPut(classMindbang *this);
void classMindbang_dGet(classMindbang *this);
void classMindbang_whlB(classMindbang *this);
void classMindbang_whlE(classMindbang *this);
void classMindbang_eval(classMindbang *this);
#endif
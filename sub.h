#ifndef SUB_H
#define SUB_H

#include "mindbang.h"

typedef	char *Sub;
typedef Sub DefSubs[256];

typedef struct SubCall SubCall;
struct SubCall {
	char *returnProc;
	TAPE_TYPE *returnPtr;
	SubCall *prev;
};

#endif	// SUB_H

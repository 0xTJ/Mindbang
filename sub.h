#ifndef SUB_H
#define SUB_H

typedef	char *Sub;
typedef Sub DefSubs[256];

typedef struct SubCall SubCall;
struct SubCall {
	char *returnProc;
	unsigned char *returnPtr;
	SubCall *prev;
};

#endif	// SUB_H

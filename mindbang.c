#include "mindbang.h"
#include "sub.h"

int mindbang_interpret(char *prog) {
	unsigned char tape[30000] = {0};
	unsigned char* ptr = tape;
	unsigned char* i;
	DefSubs defSubs;
	SubCall *curSubCall = NULL;
	SubCall *prevSubCall;
	int cBr;
	while (*prog) {
		switch (*prog) {
		case '~':
			for (i = tape; i <= ptr; i++) {
				printf("%d ", *i);
			}
			printf("\n");
			break;
		case '$':
			if (defSubs[*ptr]) {
				prevSubCall = curSubCall;
				curSubCall = malloc(sizeof(SubCall));
				curSubCall->prev = prevSubCall;
				curSubCall->returnProc = prog;
				curSubCall->returnPtr = ptr;
				prog = defSubs[*ptr] - 1;
			}
			else {
				return SubNotDef;
			}
			break;
		case '(':
			cBr = 1;
			defSubs[*ptr] = prog + 1;
			do {
				prog++;
				if (*prog == '(') cBr++;
				else if (*prog == ')') cBr--;
			} while ( cBr != 0 );
			break;
		case ')':
			if (!curSubCall)
				return UnxpctdSubEnd;
			prog = curSubCall->returnProc;
                        ptr = curSubCall->returnPtr;
                        prevSubCall = curSubCall->prev;
                        free(curSubCall);
                        curSubCall = prevSubCall;
			break;
		case ';':
			if (!curSubCall)
				return Success;
			prog = curSubCall->returnProc;
			ptr = curSubCall->returnPtr;
			prevSubCall = curSubCall->prev;
			free(curSubCall);
			curSubCall = prevSubCall;
			break;
		case '#':
			*prog = *ptr;
			--prog;
			break;
		case '>':
			++ptr;
			break;
		case '<':
			--ptr;
			break;
		case '+':
			++*ptr;
			break;
		case '-':
			--*ptr;
			break;
		case '.':
			putchar(*ptr);
			break;
		case ',':
			*ptr=getchar();
			break;
		case '[':
			if (!*ptr) {
				cBr = 1;
				do {
					prog++;
					if (*prog == '[') cBr++;
					else if (*prog == ']') cBr--;
				} while ( cBr != 0 );
			}
			break;
		case ']':
			if (*ptr) {
				int cBr = 1;
				do {
					prog--;
					if (*prog == '[')
						cBr--;
					else if (*prog == ']')
						cBr++;
				} while ( cBr != 0 );
			}
			break;
		}
		prog++;
	}
	return Failure;
}

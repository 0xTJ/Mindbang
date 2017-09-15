#include "mindbang.h"
#include "sub.h"

TAPE_TYPE tape[32768] = {0};
TAPE_TYPE *ptr = tape;
TAPE_TYPE *i;
DefSubs defSubs;
SubCall *curSubCall = NULL;
SubCall *prevSubCall;
int cBr;
int retVal;
char *prog;

int mindbang_interpret(char *program_string, FILE *instream, FILE *outstream) {
	prog = program_string;
	while (*prog) {
		retVal = Success;
		switch (*prog) {
			case '\0':
				retVal = ExitSuccess;
				break;
			case '~':
				retVal = debug_print();
				break;
			case '$':
				retVal = sub_call();
				break;
			case '(':
				retVal = start_sub_def();
				break;
			case ')':
				retVal = end_sub_def();
				break;
			case ';':
				retVal = return_sub_def();
				break;
			case '#':
				*(prog - 1) = *(ptr++);
				break;
			case '/':
				prog += *ptr;
				break;
			case '\\':
				prog -= *ptr;
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
				retVal = start_while();
				break;
			case ']':
				retVal = end_while();
				break;
			case '^':
				if (*(prog + 1) > 47 &&
					*(prog + 1) < 58 &&
					*(prog + 2) > 47 &&
					*(prog + 2) < 58 &&
					*(prog + 3) > 47 &&
					*(prog + 3) < 58) {
					*ptr = (*(prog + 1) - 48) * 100 + (*(prog + 2) - 48) * 10 + (*(prog + 3) - 48) * 1;
				}
				else
					return BadIntInProg;
				break;
		}
		if (retVal != Success)
			return retVal;
		prog++;
	}
	return Failure;
}

int debug_print() {
	for (i = tape; i <= ptr; i++) {
		printf("%d ", *i);
	}
	printf("\n");
	return Success;
}

int sub_call() {
	if (defSubs[*ptr]) {
		prevSubCall = curSubCall;
		curSubCall = malloc(sizeof(SubCall));
		curSubCall->prev = prevSubCall;
		curSubCall->returnProc = prog;
		curSubCall->returnPtr = ptr;
		prog = defSubs[*ptr] - 1;
		return Success;
	}
	else {
		return SubNotDef;
	}
}

int start_sub_def() {
	int cBr = 1;
	defSubs[*ptr] = prog + 1;
	do {
		prog++;
		if (*prog == '(') cBr++;
		else if (*prog == ')') cBr--;
		else if (*prog == '\0') return NullBe4Bracket;
	} while ( cBr != 0 );
	return Success;
}

int end_sub_def() {
	if (!curSubCall)
		return UnxpctdSubEnd;
	prog = curSubCall->returnProc;
	ptr = curSubCall->returnPtr;
	prevSubCall = curSubCall->prev;
	free(curSubCall);
	curSubCall = prevSubCall;
	return Success;
}

int return_sub_def() {
	if (!curSubCall)
		return ExitSuccess;
	prog = curSubCall->returnProc;
	ptr = curSubCall->returnPtr;
	prevSubCall = curSubCall->prev;
	free(curSubCall);
	curSubCall = prevSubCall;
	return Success;
}

int start_while() {
	if (!*ptr) {
		int cBr = 1;
		do {
			prog++;
			if (*prog == '[') cBr++;
			else if (*prog == ']') cBr--;
			else if (*prog == '\0') return NullBe4Bracket;
		} while ( cBr != 0 );
	}
	return Success;
}

int end_while() {
	if (*ptr) {
		int cBr = 1;
		do {
			prog--;
			if (*prog == '[') cBr--;
			else if (*prog == ']') cBr++;
			else if (*prog == '\0') return NullBe4Bracket;
		} while ( cBr != 0 );
	}
	return Success;
}

#include "mindbang.h"

void mindbang_interpret(char *prog) {
	unsigned char tape[30000] = {0};
	unsigned char* ptr = tape;
	unsigned char* i;
	while (*prog) {
		switch (*prog) {
		case '#':
			printf("DEBUGGING:\n");
			for (i = tape; i <= ptr; i++) {
				printf("%d ", *i);
			}
			printf("\n");
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
				int cBr = 1;
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
}

#include "mindbang.h"

unsigned char tape[30000] = {0};
unsigned char* ptr = tape;

void mindbang_interpret(char *prog) {
    while (*prog) {
		printf("%d", *prog);
		switch (*prog) {
		case '>':
			++ptr;
			break;
		case '<':
			++ptr;
			break;
		case '+':
			++*ptr;
			break;
		case '-':
			printf("About to reduce addr %d from %d\n", ptr, *ptr);
			--*ptr;
			printf("Reduced addr %d to %d\n", ptr, *ptr);
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
				prog++;
			}
			printf("NOW AT %d with character %c\n", (char)prog, *prog);
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
				++prog;
			}
			printf("NOW AT %d with character %c\n", (char)prog, *prog);
			break;
		}
		prog++;
	}
}
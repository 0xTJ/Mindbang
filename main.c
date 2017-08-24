#include "mindbang.h"

int main() {
	Mindbang *myMb = newMindbang(malloc(100 * sizeof(char)), 100);
	putchar((int)myMb->pProg);
	return 0;
}
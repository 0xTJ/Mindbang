#include "mindbang.h"

int main() {
	mindbang_interpret(",[.[-],]\0");
	return 0;
}
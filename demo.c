#include "mindbang.h"

int main() {
	char tmp[100];
	int i;
	for (i = 0; i < 11; i++) {
		tmp [i] = '+';
	}
	tmp[11] = '.';
	tmp[12] = '\0';
	
	classMindbang *myMb = classMindbang_new(tmp, 100);
	classMindbang_eval(myMb);
	
	return 0;
}
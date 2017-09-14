#ifndef MINDBANG_H
#define MINDBANG_H

#include <stdio.h>
#include <stdlib.h>

enum exit_codes{Success, Failure, SubNotDef, UnxpctdSubEnd};

int mindbang_interpret(char *prog);

#endif

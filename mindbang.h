#ifndef MINDBANG_H
#define MINDBANG_H

#include <stdio.h>
#include <stdlib.h>

#define TAPE_TYPE unsigned int

enum exit_codes{ExitSuccess, Success, NullBe4Bracket, Failure, SubNotDef, UnxpctdSubEnd, BadIntInProg};

int mindbang_interpret(char *program_string, FILE *instream, FILE *outstream);
int debug_print();
int sub_call();
int start_sub_def();
int end_sub_def();
int return_sub_def();
int start_while() ;
int end_while();

#endif

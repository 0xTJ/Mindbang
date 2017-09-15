#include <argp.h>
#include "mindbang.h"

// A COOL DEMO: mbang -p "^091>^044>^046>^093<<<####^007\\"

/* This structure is used by main to communicate with parse_opt. */
struct arguments
{
	char *args[0];			/* ARG1 */
	char *program, *progfile;	/* Argument for -f */
	char *infile, *outfile;	/* Argument for -i, -o */
};

/*
   OPTIONS.  Field 1 in ARGP.
   Order of fields: {NAME, KEY, ARG, FLAGS, DOC}.
*/
static struct argp_option options[] =
{
	{   "program",   'p', "PROG", 0,
		"Use PROG as program to be run"
	},
	{   "progfile",  'f', "PROGFILE", 0,
		"Input from PROGFILE as program"
	},
	{   "input",  'i', "INFILE", 0,
		"Input from INFILE instead of from standard input"
	},
	{   "output",  'o', "OUTFILE", 0,
		"Output to OUTFILE instead of to standard output"
	},
	{0}
};


/*
   PARSER. Field 2 in ARGP.
   Order of parameters: KEY, ARG, STATE.
*/
static error_t
parse_opt (int key, char *arg, struct argp_state *state)
{
	struct arguments *arguments = state->input;

	switch (key)
	{
	case 'p':
		arguments->program = arg;
		break;
	case 'f':
		arguments->progfile = arg;
		break;
	case 'i':
		arguments->infile = arg;
		break;
	case 'o':
		arguments->outfile = arg;
		break;
	case ARGP_KEY_ARG:
		if (state->arg_num >= 0)
		{
			argp_usage(state);
		}
		arguments->args[state->arg_num] = arg;
		break;
	case ARGP_KEY_END:
		if (state->arg_num < 0)
		{
			argp_usage (state);
		}
		break;
	default:
		return ARGP_ERR_UNKNOWN;
	}
	
	return 0;
}

/*
   ARGS_DOC. Field 3 in ARGP.
   A description of the non-option command-line arguments
	 that we accept.
*/
//static char args_doc[] = "ARG1";
static char args_doc[] = "";

/*
  DOC.  Field 4 in ARGP.
  Program documentation.
*/
static char doc[] =
	"argex -- A program to demonstrate how to code command-line options	and arguments.\vFrom the GNU C Tutorial.";	// TODO: Try again

/*
   The ARGP structure itself.
*/
static struct argp argp = {options, parse_opt, args_doc, doc};

int main(int argc, char* argv[]) {
	
	struct arguments arguments;
	FILE *instream;
	FILE *outstream;
	FILE *progstream;
	char *program_string;
	
	/* Set argument defaults */
	arguments.program = NULL;
	arguments.progfile = NULL;
	arguments.infile = NULL;
	arguments.outfile = NULL;
	argp_parse (&argp, argc, argv, 0, 0, &arguments);

	if (!arguments.program == !arguments.progfile) {
		printf("Exactly one of -p and -f must be specified\n");
		return 255;
	}
	
	if (arguments.program) {
		program_string = arguments.program;
	}
	else if (arguments.progfile) {
		progstream = fopen (arguments.progfile, "r");
		if (progstream) {
			long length;
			
			fseek (progstream, 0, SEEK_END);
			length = ftell (progstream);
			fseek (progstream, 0, SEEK_SET);
			program_string = malloc (length);
			if (program_string) {
				fread (program_string, 1, length, progstream);
			}
			fclose (progstream);
		}
	}
	
	if (arguments.infile)
		instream = fopen (arguments.infile, "r");
	else
		instream = stdin;
	
	if (arguments.outfile)
		outstream = fopen (arguments.outfile, "w");
	else
		outstream = stdout;
	
	return mindbang_interpret(program_string, instream, outstream);
}

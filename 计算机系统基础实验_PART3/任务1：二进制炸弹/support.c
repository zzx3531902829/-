#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "support.h"

extern FILE *infile;

char input_strings[MAX_STRINGS][MAX_LINE];
int num_input_strings = 0;
//char scratch[MAX_LINE];


/* Invoked by improperly built phases */
void invalid_phase(char *s) 
{
    printf("Invalid phase%s\n", s);
    exit(8);
}

/* Extract numbers from an input string */
 void read_six_numbers(char *input, int *numbers)
{
  int numScanned = sscanf(input, "%d %d %d %d %d %d",
			  numbers, numbers + 1, numbers + 2,
			  numbers + 3, numbers + 4, numbers + 5);
  if (numScanned < 6)
    explode_bomb();
}

/* A more user-friendly version of strlen */
int string_length(char *aString)
{
    int length;
    char *ptr;

    ptr = aString;
    length = 0;

    while (*ptr != 0) {
	ptr++;
	length = length + 1;
    }
    return length;
}

/* A more user-friendly version of strcmp */
int strings_not_equal(char *string1, char *string2)
{
    char *p, *q;

    if (string_length(string1) != string_length(string2))
	return 1;
    p = string1;
    q = string2;
    while (*p != 0) {
	if (*p != *q)
	    return 1;
	p++;
	q++;
    }
    return 0;
}


/* Return true if str is a blank line */
int blank_line(char *str)
{
    while (*str)
	if (!isspace(*str++))
	    return 0;
    return 1;
}

/* Read input lines until first non-blank or EOF encountered */
char *skip() 
{
    char *p;

    while (1) {
	p = fgets(input_strings[num_input_strings], MAX_LINE, infile);
	if ((p == NULL) || (!blank_line(p)))
	    return p;
    }
}

/* 
 * Read a line of input from stream "infile". There are a couple
 * of tricky aspects to this. First, we cut the students a little slack
 * by skipping over blank lines. Second, we allow partial solutions
 * to be read from a file before switching over to stdin.
 */
char *read_line(void)
{
    int len;
    char *str;

    /* switch over to stdin if we hit EOF on an input disk file */
    str = skip();
    if (str == NULL) { /* EOF */
	if (infile == stdin) { /* premature EOF on stdin */
	    printf("Error: Premature EOF on stdin\n");
	    exit(8);
	}
	else {
	    /* exit with OK status on EOF if we are grading the bomb */
	    /* this lets us evaluate partial solutions */
	    if (getenv("GRADE_BOMB")) {
		exit(0); 
	    }

	    /* otherwise switch over to stdin */
	    else {
		infile = stdin; 
		str = skip();
		if (str == NULL) { /* premature EOF on stdin */
		    printf("Error: Premature EOF on stdin\n");
		    exit(0);
		}
	    }
	}
    }

    len = strlen(input_strings[num_input_strings]);
    if(len >= MAX_LINE-1) {
	printf("Error: Input line too long\n");
	strcpy(input_strings[num_input_strings++], "***truncated***");
	explode_bomb();
    }

    /* Strip off trailing newline: */
    input_strings[num_input_strings][len-1] = '\0';
    return input_strings[num_input_strings++];
}


void explode_bomb(void)
{
    printf("\n BOOM !  \n You failed \n");
    exit(8);
}




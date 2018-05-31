#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/**
 * SETTINGS for the maximums.
 */

#define MAXOPTIONS 5 // max options per line/command
#define MAXOPTIONARGS 3 //max arguments per option (these are option args like cmd -i 4 -o 10)
#define MAXARGS 5 // max arguments (for the command, these are seperate from arguments for options)
/* Lengths */
#define MAXLINELENGTH 5000 // max line length (user command line input)
#define MAXOPTIONLENGTH 5 // max length of an option (10 is very generous...)
#define MAXARGLENGTH 1026 // because 1024 + 2 * " (quotes...)


/**
 * Structure for our options
 */
struct nixOption {
	char flag[MAXOPTIONLENGTH];
	char arg[MAXOPTIONLENGTH][MAXARGLENGTH];
};

/**
 * The structure for our shell variable.
 */
struct nix {
	char *input;
	char *command;
	struct nixOption *optionsList;
	char *argList;
	char coolSymbol[3];
	char coolTitle[32];
	unsigned int debug;
} nixShell;


/**
 * Processes... Init, End, Refresh & Loop
 */
void nixInitShell(char *coolSymbol, char *shellTitle);
void nixRefreshShell();
void nixEndShell();
int nixLoopShell();

/**
 * Get Functions...
 */
char *nixGetArg(int n);
int nixGetOptIndex(char *option);
struct nixOption *nixGetOpt(char *option);


/**
 * Misc functions
 */
int getline2(char s[], int lim);
int nixParseCommand(char *input, char *cmd, struct nixOption *optionsList, char *argList);
void nixRemoveQuotes(char *str);
void nixMessage();
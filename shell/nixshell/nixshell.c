/*
* @Author: albin
* @Date:   2018-05-01 17:56:49
* @Last Modified by:   albin
* @Last Modified time: 2018-05-31 20:05:29
*/


#include "./nixshell.h"

/**
 * From the Book K&R. It's so good you want to steal it.
 * @param  s   String.
 * @param  lim Limit.
 * @return     Integer.
 */
int getline2(char s[], int lim) {
	//getline2 from K&R book.
	int c, i;
	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

/**
 * nixParseCommand parses the line and modifes the variable and lists passed to
 * the function as parameters.
 * @param  input       The input (command-line) to be parsed.
 * @param  cmd         A pointer to a char, where the command will be stored.
 * @param  optionsList A pointer to an array of struct nixOption, where the options will be stored
 * @param  argList     A pointer to an array of strings.
 * @return             Returns always 0.
 */
int nixParseCommand(char *input, char *cmd, struct nixOption *optionsList, char *argList) {


	unsigned int debug = nixShell.debug;

	//removes the \n at the end of the line
	int lastLine;
	lastLine = strlen(input) - 1;
	if (input[lastLine] == '\n') input[lastLine] = '\0';


	char tmp[MAXARGLENGTH];
	char *list = malloc((MAXOPTIONS * MAXOPTIONARGS + MAXOPTIONS * MAXARGS) * MAXARGLENGTH * sizeof(char));

	unsigned int quoteMode = 0;
	unsigned int escapeMode = 0;
	int listCounter = 0;
	int tmpCounter = 0;

	for (int i = 0; i < strlen(input) + 1; ++i) {

		if ((int) input[i] == 92) escapeMode = 1;

		if ((int) input[i] == 34 && escapeMode == 0) { //quote!
			if (quoteMode == 0) quoteMode = 1;
			else quoteMode = 0;
		}

		if ((int) input[i] == 34 && escapeMode == 1) {
			//turn off escapemode
			escapeMode = 0;
		}

		//if char isnt space or the quotemode is on => append
		// AND:  (in both cases) char is not NUL char.
		if (((int) input[i] != 32 || quoteMode) && (int) input[i] != 0) { //32 = space, 0= null terminator
			//if no space, append it to our tmp var
			tmp[tmpCounter++] = input[i];
		}
		else {
			if (strlen(tmp) != 0) { //if not empty
				tmp[tmpCounter++] = (char) 0;

				//if space, add tmp to list
				nixRemoveQuotes(tmp); //remove quotes first
				strcpy(list + MAXARGLENGTH * listCounter++, tmp);

				//clear tmp
				memset(&tmp[0], 0, sizeof(tmp));
				tmpCounter = 0;
			}
		}
	}


	//now let's sort/categorize this list.
	//check if it's an option (if it has a "-" as first arg),
	//if yes & the following is an argument (not an option), then add the argument
	//as the "arg" in the structure
	char *p;
	char *listElement;
	int optionsCounter = 0;
	int argsCounter = 0;
	int optionFound = 0;
	for (int i = 0; i < 15; ++i) {
		listElement = list + MAXARGLENGTH * i;

		//if first char is a "-", then it's an option
		if (*(listElement) == '-') {
			strcpy((optionsList + optionsCounter)->flag, listElement);

			if (debug) printf("%i# %s\n", optionsCounter, (optionsList + optionsCounter)->flag);

			optionFound = 0;
			//now, keep looking for arguments that follow this option
			for (int j = 0; j < 5; ++j) { //5 because max arguments per option
				p = (listElement + MAXARGLENGTH * (j + 1));
				if (*p == '-' || (int) *p == 0) break; //if not - or null, it's an arg.
				strcpy((optionsList + optionsCounter)->arg[j], p);
				if (debug) printf("%i## %i: %s\n", optionsCounter, j, (optionsList + optionsCounter)->arg[j]);
				optionFound = 1;
			}

			if (optionFound) {
				optionFound = 0;
			}

			optionsCounter++;
		}

		//if it's not an option, it must be an argument,
		//so add it to our argument list

		else {

			//well it's not yet clear if it's really an argument.
			//if i==0, then it's the command, since the command is always the first one
			//further: if the argument is followed by an option OR multiple arguments and then
			//an option, then it's an argument for the option, so we won't add it to our list.

			optionFound = 0;
			if (i != 0) { //if not command
				for (int j = 0; j < 5; ++j) { //5 because max arguments per option
					p = &(*(listElement + MAXARGLENGTH * (j + 1)));
					if (*p == '-') optionFound = 1;
				}

				if (!optionFound && (int) *listElement != 0) {
					//add it to our arg list
					strcpy((argList + argsCounter * MAXARGLENGTH), listElement);
					if (debug) printf("%i# Arg: %s\n", argsCounter, listElement);
					argsCounter++;
				}

			}


		}

	}

	//and finally put the command to cmd
	strcpy(cmd, list);

	//reset and release the memory
	memset(&list[0], 0, (MAXOPTIONS * MAXOPTIONARGS + MAXOPTIONS * MAXARGS) * MAXARGLENGTH * sizeof(char) + 1);
	free(list);

	return 0;

}


/**
 * Removes quotes from the beginning of a string and the end.
 * @param string [description]
 */
void nixRemoveQuotes(char *string) {
	char tmp;
	int c = 0;
	for (int i = 0; i < strlen(string) + 1; ++i)
	{
		if ((int) string[i] == 34 && (i == 0 || i == strlen(string) - 1)) {
			//if first and last quote, shift (skip)
			continue;
		}

		string[c++] = string[i];
	}

}

/**
 * Initializes the shell.
 */
void nixInitShell(char *coolSymbol, char *coolTitle) {
	printf("%s", coolTitle); //show the title
	printf("\n%s", coolSymbol); //show the cool symbol

	strcpy(nixShell.coolSymbol, coolSymbol);
	strcpy(nixShell.coolTitle, coolTitle);
	//allocate memory
	nixShell.input = malloc(MAXLINELENGTH * sizeof(char));
	nixShell.command = malloc(MAXARGLENGTH * sizeof(char));
	nixShell.optionsList = (struct nixOption *) malloc(MAXOPTIONS * sizeof(struct nixOption));
	nixShell.argList = malloc(MAXARGS * MAXARGLENGTH * sizeof(char));
}

/**
 * Ends the shell by freeing allocated memory.
 */
void nixEndShell() {
	free(nixShell.input);
	free(nixShell.command);
	free(nixShell.optionsList);
	free(nixShell.argList);
}

/**
 * Refreshes the shell by settings the memory of
 * the command, optionsList and argList to 0.
 */
void nixRefreshShell() {
	printf("%s", nixShell.coolSymbol);
	memset(&nixShell.input[0], 0, sizeof(nixShell.input));
	memset(&nixShell.command[0], 0, sizeof(nixShell.command));
	memset(&nixShell.optionsList[0], 0, sizeof(*nixShell.optionsList));
	memset(&nixShell.argList[0], 0, sizeof(nixShell.input));
}

/**
 * Loops the shell.
 * @return getline2 > 0
 */
int nixLoopShell() {
	int loop = (getline2(nixShell.input, MAXLINELENGTH) > 0);

	nixParseCommand(nixShell.input, nixShell.command, nixShell.optionsList, nixShell.argList);
	return loop;
}

/**
 * Displays a message on the shell.
 * @param message A string.
 */
void nixMessage(char *message) {
	printf("%s\n", message);
}

/**
 * Returns the n-th argument
 * @param  n Integer starting at 0.
 * @return   Returns a string containing the n-th argument.
 */
char *nixGetArg(int n) {
	return nixShell.argList + MAXARGLENGTH * n;
}

/**
 * Returns a struct nixOption, the n-th option.
 * @param  n [description]
 * @return   struct nixOption
 */
struct nixOption *nixGetOpt(char *option) {
	int optionIndex = nixGetOptIndex(option);
	if (optionIndex > -1) {
		return nixShell.optionsList + optionIndex;
	}
	else {
		return NULL;
	}
}


/**
 * Returns the position of the option, if that option hasnt been entered, returns -1.
 * @param  option      A string, the option to get.
 * @return             Returns position of option. If option not found, returns -1.
 */
int nixGetOptIndex(char *option) {
	char optionWrapper[MAXOPTIONLENGTH] = "-";
	strcat(optionWrapper, option);

	for (int i = 0; i < MAXOPTIONS; ++i) {
		if (strlen((nixShell.optionsList + i)->flag) > 0) {
			if (strcmp(optionWrapper, (nixShell.optionsList + i)->flag) == 0) {
				return i;
			}
		}
	}
	return -1;
}

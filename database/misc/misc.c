/*
* @Author: albin
* @Date:   2018-04-23 11:11:27
* @Last Modified by:   albin
* @Last Modified time: 2018-05-29 01:48:48
*/

#include "./misc.h"

/**
 * Variables, where you want a match to be stored, have to be initialized with
 * newMatch(). This way, the library handles all malloc and free of memory.
 * @return Returns a pointer.
 */
char *newMatch() {
	//allocate memory (an array of 1024 chars)
	char *str = (char *) malloc(sizeof(char) * MAXENTRYLENGTH);

	//put it into our matchvariables array, so we can free it afterwards, without user input
	extern char **matchVariables;
	extern int matchCounter;
	extern int matchVariablesAvailable;
	if (matchVariablesAvailable <= matchCounter) {
		//reallocate, make more space for our matchVariables
		matchVariablesAvailable = matchVariablesAvailable + 10;
		matchVariables = (char**) realloc(matchVariables, matchVariablesAvailable * sizeof(char*));
	}

	//assign it and increase our counter
	matchVariables[matchCounter] = str;
	matchCounter++;

	return str;
}

/**
 * Lists all entries that are currently in the database stored.
 */
void listAllEntries() {
	char *elements[3];
	extern char *ptr;
	extern int pos;

	printf("============================ TABLE ============================\n");
	for (int i = 0; i < pos; ++i) {

		//shortcuts for the elements
		elements[0] = (ptr + (0 + i * 3) * MAXENTRYLENGTH);
		elements[1] = (ptr + (1 + i * 3) * MAXENTRYLENGTH);
		elements[2] = (ptr + (2 + i * 3) * MAXENTRYLENGTH);
		if (strlen(elements[0]) > 0 || strlen(elements[1]) > 0 || strlen(elements[2]) > 0) {
			printf("%s | %s | %s\n", elements[0], elements[1], elements[2]);
		}
	}
	printf("========================= END  TABLE ==========================\n");
}
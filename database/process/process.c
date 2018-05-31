/*
* @Author: albin
* @Date:   2018-04-23 10:15:30
* @Last Modified by:   albin
* @Last Modified time: 2018-05-29 01:50:44
*/

#include "./process.h"

/**
 * Initializes the database by allocation memory, etc.
 * @return 	Returns 0 if everything's okey, 1 if an error occured.
 */
int initProcess() {

	// ALLOCATE FIXED MEMORY
	// 100 available sets of 3 triplets. each set has 3 triplets each having 1024 chars.
	//i.e. an array[1024];
	extern char *ptr;
	extern int pos;
	ptr = (char*) malloc(MAXDBSIZE * 3 * MAXENTRYLENGTH * sizeof(char));
	pos = 0;

	//IF ALLOCATION DIDNT WORK
	if (ptr == NULL) {
		printf("Error allocating memory! #1\n");
		exit(1);
		return 1;
	}

	// ALLOCATE MEMORY FOR THE LIST OF USED POINTERS FOR MATCHES
	extern char **matchVariables;
	extern int matchCounter;
	extern int matchVariablesAvailable;
	// start with 10 available variables. increase if needed
	matchVariablesAvailable = 10;
	matchVariables = (char**) malloc(matchVariablesAvailable * sizeof(char*));
	matchCounter = 0;

	if (matchVariables == NULL) {
		printf("Error allocating memory! #2\n");
		exit(1);
		return 1;
	}

	return 0;
}

/**
 * Ends the process by freeing memory.
 * @return Returns 0 if everything's okey, 1 if an error occured.
 */
int endProcess() {

	//free allocated memory for our database
	extern char *ptr;
	free(ptr);

	//free all used variables for matches.
	extern char **matchVariables;
	extern int matchCounter;
	for (int i = 0; i < matchCounter; ++i)
	{
		free(matchVariables[i]);
	}

	//and finally free our matchVariables.
	free(matchVariables);

	return 0;
}

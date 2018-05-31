#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "./../config.h"
#include "./../insert/insert.h"
#include "./../match/match.h"
#include "./../misc/misc.h"


// GLOBAL VARIABLES
int pos; // the current position (increases after every insertion)
char *ptr; // the pointer to the allocated memory for insertion and matching
char **matchVariables; // a list of pointers
int matchCounter;
int matchVariablesAvailable; //tells us how many variables are actually available


int initProcess();
int endProcess();

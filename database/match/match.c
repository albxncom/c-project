/*
* @Author: albin
* @Date:   2018-04-06 00:58:57
* @Last Modified by:   albin
* @Last Modified time: 2018-05-29 01:45:09
*/

#include "./match.h"

struct fields {
	unsigned int first : 1;
	unsigned int second : 1;
	unsigned int third : 1;
};

/**
 * The match function searches the database for a given S, P or O.
 * It returns the resul-th entry by putting the results into the given
 * S, P or O variable which have to be initialized with newMatch().
 *
 * @param  s      String or newMatch(), first string to match.
 * @param  p      String or newMatch(), second string to match.
 * @param  o      String or newMatch(), third string to match.
 * @param  result Long, which entry to match.
 * @return        Returns 0 if there was a match, otherwise returns 1. (C logic)
 */
int match(char *s, char *p, char *o, long result) {

	extern int pos;
	extern char *ptr;


	long resultsPos = 0;
	char *elements[3];

	struct fields toMatchFields = {
		((strcmp(s, "") != 0) ? 1 : 0),
		((strcmp(p, "") != 0) ? 1 : 0),
		((strcmp(o, "") != 0) ? 1 : 0)
	};

	struct fields matchedFields = { 0, 0, 0 };
	int addMe = 0;

	for (int i = 0; i < pos; ++i)
	{
		//reset resultFields
		matchedFields.first = 0;
		matchedFields.second = 0;
		matchedFields.third = 0;


		//shortcuts for the elements
		elements[0] = (ptr + (0 + i * 3) * MAXENTRYLENGTH);
		elements[1] = (ptr + (1 + i * 3) * MAXENTRYLENGTH);
		elements[2] = (ptr + (2 + i * 3) * MAXENTRYLENGTH);

		// MATCHES
		// C starts comparing from left to right, so strcmp should be compared as
		// second because it's faster to check the bitfield!
		if (toMatchFields.first && strcmp(elements[0], s) == 0) {
			//first match
			matchedFields.first = 1;
		}

		if (toMatchFields.second && strcmp(elements[1], p) == 0) {
			//second match
			matchedFields.second = 1;
		}

		if (toMatchFields.third && strcmp(elements[2], o) == 0) {
			//third match
			matchedFields.third = 1;
		}


		if (matchedFields.first == toMatchFields.first &&
		        matchedFields.second == toMatchFields.second &&
		        matchedFields.third == toMatchFields.third
		   ) {
			// MATCH!!!!!!

			//now only return if result == pos
			if (result == resultsPos)
			{
				if (matchedFields.first == 0) strcpy(s, elements[0]);
				if (matchedFields.second == 0) strcpy(p, elements[1]);
				if (matchedFields.third == 0) strcpy(o, elements[2]);

				return 0;
			}
			//otherwise, skip
			else {
				resultsPos++;
			}


		}


	}

	//nothing found
	return 1;
}

/*
* @Author: albin
* @Date:   2018-04-06 00:59:01
* @Last Modified by:   albin
* @Last Modified time: 2018-05-29 01:39:16
*/

#include "./insert.h"

/**
 * The insert function stores a triplet  into the memory.
 * @param  s First string to store.
 * @param  p Second string to store.
 * @param  o Third string to store.
 * @return   Always 0, no meaning.
 */
int insert(char *s, char *p, char *o) {
	extern char *ptr;
	extern int pos;

	//copy the args to every array slot of 1024 byte each.
	strcpy((ptr + (0 + pos * 3)*MAXENTRYLENGTH), s);
	strcpy((ptr + (1 + pos * 3)*MAXENTRYLENGTH), p);
	strcpy((ptr + (2 + pos * 3)*MAXENTRYLENGTH), o);

	pos++;
	return 0;
}

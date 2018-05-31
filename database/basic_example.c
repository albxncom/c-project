/*
* @Author: albin
* @Date:   2018-04-06 00:53:27
* @Last Modified by:   albin
* @Last Modified time: 2018-05-29 18:40:47
*/

/**
 * This is an example file on how to use this library.
 */


#include "./process/process.h"

int main() {

	//allocates memory and sets the process going...
	initProcess();


	//insert
	insert("albin", "jutzet", "bobby");
	insert("albin", "jutzet", "hans");
	insert("albin", "jutzet", "marina");


	//match
	//set p and o to NULL if you want a return value
	char s[] = "albin";
	char p[] = "jutzet";
	char *o = newMatch();


	match(s, p, o, 1);

	printf("%s; %s; %s\n", s, p, o);
	o = newMatch();
	match(s, p, o, 2);

	printf("%s; %s; %s\n", s, p, o);

	//	frees memory and ends the process..
	endProcess();
}

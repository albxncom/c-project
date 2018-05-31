# \*nixShell

This library allows to implement a simple \*nix - like shell into your application. It supports options (`cmd - l - m`), arguments for options (`cmd - l 2 - m 4`), normal, quote arguments and escaping (`cmd - l true "Hello \"World\"!!!"`). Escaping works on option arguments, too. It uses no regex, so it runs almost everywhere.

# Usage

To use the shell within your project, include the `. / shell / shell.h` file into your main file. Initialize the shell with `initShell()`. Then : Implement a while loop, with the statement `nixLoopShell()`. Just before the end of your while loop, refresh the shell with `nixRefreshShell()`. And at the end of your program, use `nixEndShell()` to free the memory, used by the shell.

## Example / Skeleton

```C
#include "./nixshell/nixshell.h"

int main() {
	nixInitShell("$ ", "SIMPLE SHELL");

	while (nixLoopShell()) {

		// Your own function, very, very simple!
		if (strcmp(nixShell.command, "sayHelloWorld") == 0) {
			nixMessage("Hello World!");
		}

		/* Not known command ... */
		else {
			char message[100];
			sprintf(message, "%s is not supported.", nixShell.command);
			nixMessage(message);
		}

		nixRefreshShell();

	}

	nixEndShell();

	return 0;
}
```


### Arguments
The library provides a function to get arguments that are passed to a command. Here's an example, use it inside the while(nixLoopShell) loop. Quote arguments work and escaping in quote arguments works, too.

```C
// Your own function with 2 arguments, also simple.
if (strcmp(nixShell.command, "sayMyName") == 0) {
	char *arg1 = nixGetArg(0);
	char *arg2 = nixGetArg(1);
	if (strlen(arg1) > 0 && strlen(arg2) > 0) {
		char message[100];
		sprintf(message, "Hello %s %s", arg1, arg2);
		nixMessage(message);
	}
	else {
		nixMessage("The command sayMyName expects two arguments.");
	}
}
```

**Use** it like `sayMyName "The Cool" Shell`



### Options
Options work great, too.

```C
if (strcmp(nixShell.command, "letsParty") == 0) {
	struct nixOption *option_dance = nixGetOpt("d");

	if (option_dance) {
		nixMessage("Party and everyone's dancing!");
	}

	if (!option_dance) {
		nixMessage("Party but no one's dancing! :-(");
	}
}
```


### Options with arguments
You can even pass multiple arguments.

```C
// Your own function with options, a bit less simple, but still simple!
if (strcmp(nixShell.command, "letsParty") == 0) {
	struct nixOption *option_songs = nixGetOpt("s");
	struct nixOption *option_dance = nixGetOpt("d");

	if (option_songs && option_dance) { //if flag for songs and dance are set
	char message[100];
	char *firstSong = option_songs->arg[0]; //takes the first arg passed to -s
	char *secondSong = option_songs->arg[1]; //second

	char *theDance = option_dance->arg[0]; //first arg

	//if there's a first song
	if (strlen(firstSong) > 0) {
		sprintf(message, "Let's dance %s to %s", theDance, firstSong);
		nixMessage(message);

		//if there's a second song
		if (strlen(secondSong) > 0) {
			sprintf(message, "... and later to %s", secondSong);
			nixMessage(message);
		}
	}
	else {
		nixMessage("Let's dance to some random music, because you didn't pass an argument to -s.");
	}

	if (!option_songs) {
		nixMessage("How do you wanna dance if there's no music? Use -s, it accepts up to two songs!");
	}

	if (!option_dance) {
		nixMessage("Oops! You forgot to define a dance. -d accepts a dance!");
	}
}
```

### System calls
Use the native system() function to run native shell commands.
```C
if (strcmp(nixShell.command, "clear") == 0) {
	system("clear");
	nixMessage("SIMPLE SHELL"); //display the title
}
```

## Documentation

```C
int getline2(char s[], int lim)
/**
 * From the Book K&R. It's so good you want to steal it.
 * @param  s   String.
 * @param  lim Limit.
 * @return     Integer.
 */
```


```C
int nixParseCommand(char *input, char *cmd, struct nixOption *optionsList, char *argList)
/**
 * nixParseCommand parses the line and modifes the variable and lists passed to
 * the function as parameters.
 * @param  input       The input (command-line) to be parsed.
 * @param  cmd         A pointer to a char, where the command will be stored.
 * @param  optionsList A pointer to an array of struct nixOption, where the options will be stored
 * @param  argList     A pointer to an array of strings.
 * @return             Returns always 0.
 */
```


```C
void nixRemoveQuotes(char *string)
/**
 * Removes quotes from the beginning of a string and the end.
 * @param string [description]
 */
```


```C
void nixInitShell(char *coolSymbol, char *coolTitle)
/**
 * Initializes the shell.
 */
```

```C
void nixEndShell()
/**
 * Ends the shell by freeing allocated memory.
 */
```

```C
void nixRefreshShell()
/**
 * Refreshes the shell by settings the memory of
 * the command, optionsList and argList to 0.
 * @return Integer. No meaning.
 */
```


```C
void nixLoopShell()
/**
 * Loops the shell.
 * @return getline2 > 0
 */
```


```C
int nixMessage()
/**
 * Displays a message on the shell.
 * @param message A string.
 */
```


```C
char *nixGetArg(int n)
/**
 * Returns the n-th argument
 * @param  n Integer starting at 0.
 * @return   Returns a string containing the n-th argument.
 */
```


```C
struct nixOption *nixGetOpt(char *option)
/**
 * Returns a struct nixOption, the n-th option.
 * @param  n [description]
 * @return   struct nixOption
 */
```


```C
int nixGetOptIndex(char *option)
/**
 * Returns the position of the option, if that option hasnt been entered, returns -1.
 * @param  option      A string, the option to get.
 * @return             Returns position of option. If option not found, returns -1.
 */
```

## Configuration
To change the configuration, edit the `shell.h` file in the root directory of the shell.

```C
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
```


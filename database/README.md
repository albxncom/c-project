# Database

This database library allows to store (`insert`) triplets {S, P, O} and read (`match`) from the triplets from the memory. 

# Usage

To use the database within your project, include the `./process/process.h` file into your main file. Before starting to `insert` and `match` data, initialize the process with `initProcess()`. At the end of your file or whenever you're done using the database, **it's very important** to clear the memory by just using `endProcess()`, it will `free` all memory used by the library. **You still have to free your own allocated memory, though!**

## Example / Skeleton
```C
#include "./process/process.h"

int main(){

	//allocates memory and sets the process going...
	initProcess();

	//insert 
	insert("first", "second", "third");
	
	//match
	char s[] = "first";
	char *p = newMatch();
	char *o = newMatch();

	match(s, p, o, 1);

	printf("%s; %s; %s\n", s, p, o);

	//	frees memory and ends the process..
	endProcess();
}
```

## Documentation
### insert

    /**
     * The insert function stores a triplet  into the memory. 
     * @param  s First string to store.
     * @param  p Second string to store.
     * @param  o Third string to store.
     * @return   Always 0, no meaning.
     */
    int insert(char *s, char *p, char *o)

### match

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
    int match(char *s, char *p, char *o, long result)

### newMatch

    /**
     * Variables, where you want a match to be stored, have to be initialized with 
     * newMatch(). This way, the library handles all malloc and free of memory.
     * @return Returns a pointer.
     */
    char *newMatch() 

### listAllEntries

    /**
     * Lists all entries that are currently in the database stored.
     */
    void listAllEntries()

### initProcess

    /**
     * Initializes the database by allocation memory, etc.
     * @return 	Returns 0 if everything's okey, 1 if an error occured.
     */
    int initProcess()

### endProcess

    /**
     * Ends the process by freeing memory.
     * @return Returns 0 if everything's okey, 1 if an error occured.
     */
    int endProcess()


## Configuration
To change the configuration, edit the `config.h` file in the root directory. Currently two options are available (default values):

    #define MAXENTRYLENGTH 1026
    #define MAXDBSIZE 100

### MAXENTRYLENGTH
This is the maximum length of S, P and O in a triplet.  Default 1026.

### MAXDBSIZE
The maximum number of triplets that can be stored. Default 100.

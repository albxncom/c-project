/*
* @Author: albin
* @Date:   2018-05-01 22:15:24
* @Last Modified by:   albin
* @Last Modified time: 2018-05-31 17:58:50
*/


/**
 * This is an example of the combination of the two libraries.
 */


#include "./../shell/nixshell/nixshell.h" //SHELL
#include "./../database/process/process.h" //DATABASE


int main() {

	//allocates memory and sets the process going...
	initProcess();

	nixInitShell("$ ", "DATABASE SHELL");

	while (nixLoopShell()) {

		/* insert */
		if (strcmp(nixShell.command, "insert") == 0) {
			struct nixOption *option_s = nixGetOpt("s");
			struct nixOption *option_p = nixGetOpt("p");
			struct nixOption *option_o = nixGetOpt("o");
			if (option_s && option_p && option_o) {
				insert(
				    option_s->arg[0],
				    option_p->arg[0],
				    option_o->arg[0]
				);
			}
			else {
				nixMessage("The command insert expects three options -s -p and -p with each having one argument.");
			}
		}

		else if (strcmp(nixShell.command, "insert2") == 0) {
			char *arg1 = nixGetArg(0);
			char *arg2 = nixGetArg(1);
			char *arg3 = nixGetArg(2);

			if (strlen(arg1) > 0 && strlen(arg2) > 0 && strlen(arg3) > 0) {
				insert(
				    arg1,
				    arg2,
				    arg3
				);
			}
			else {
				nixMessage("The command insert2 expects three arguments.");
			}
		}

		/* match */
		else if (strcmp(nixShell.command, "match") == 0) {
			struct nixOption *option_s = nixGetOpt("s");
			struct nixOption *option_p = nixGetOpt("p");
			struct nixOption *option_o = nixGetOpt("o");
			struct nixOption *option_r = nixGetOpt("r");


			if (option_s || option_p || option_o) {
				char *s = (option_s) ? option_s->arg[0] : newMatch();
				char *p = (option_p) ? option_p->arg[0] : newMatch();
				char *o = (option_o) ? option_o->arg[0] : newMatch();
				long r = (option_r) ? (long)((int) * (option_r->arg[0]) - 48) : (long) 0;

				if (!match(s, p, o, r)) {
					char message[MAXARGLENGTH * 3 + 10];

					sprintf(message, "Matched result #%ld: %s | %s | %s", r, s, p, o);

					nixMessage(message);
				}

				else {
					nixMessage("No result matched. Hit up ls to list all entries.");
				}

			}

			else {
				nixMessage("The command match expects at least one parameter -s, -p or -o.");
			}
		}


		/* ls */
		else if (strcmp(nixShell.command, "ls") == 0) {
			listAllEntries();
		}

		/* clear */
		else if (strcmp(nixShell.command, "clear") == 0) {
			system("clear");
			nixMessage("DATABASE SHELL");
		}

		/* not known command ... */
		else {
			char message[MAXARGLENGTH + 25];
			sprintf(message, "%s is not supported.", nixShell.command);
			nixMessage(message);
		}

		nixRefreshShell();
	}

//	frees memory and ends the process..
	endProcess();
	nixEndShell();

	return 0;
}

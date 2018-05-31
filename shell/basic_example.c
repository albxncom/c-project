#include "./nixshell/nixshell.h" //SHELL

int main() {

	char coolSymbol[] = "$ "; //some cooly symbol...
	char coolTitle[] = "COOL SHELL"; //cool shell name

	nixInitShell(coolSymbol, coolTitle);

	//this is debug mode on. set it to 0 so you don't see every time
	//the catched args and options listed after every input
	nixShell.debug = 1;

	while (nixLoopShell()) {

		// Your own function, very, very simple!
		if (strcmp(nixShell.command, "sayHelloWorld") == 0) {
			nixMessage("Hello World!");
		}

		// Your own function with 2 arguments, also simple.
		else if (strcmp(nixShell.command, "sayMyName") == 0) {
			char * arg1 = nixGetArg(0);
			char * arg2 = nixGetArg(1);

			if (strlen(arg1) > 0 && strlen(arg2) > 0) {
				char message[100];
				sprintf(message, "Hello %s %s", arg1, arg2);
				nixMessage(message);
			}
			else {
				nixMessage("The command sayMyName expects two arguments.");
			}
		}

		// Your own function with options, a bit less simple, but still simple!
		else if (strcmp(nixShell.command, "letsParty") == 0) {
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
			}

			if (!option_songs) {
				nixMessage("How do you wanna dance if there's no music? Use -s, it accepts up to two songs!");
			}

			if (!option_dance) {
				nixMessage("Oops! You forgot to define a dance. -d accepts a dance!");
			}
		}

		/* clear */
		else if (strcmp(nixShell.command, "clear") == 0) {
			system("clear");
			nixMessage("SIMPLE SHELL");
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

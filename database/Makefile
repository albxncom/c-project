all : basic_example

clean_all:
	rm basic_example *.o
	rm ./insert/*.o
	rm ./match/*.o
	rm ./process/*.o
	rm ./misc/*.o


# basic_example
#-------
basic_example : basic_example.o ./misc/misc.o ./process/process.o ./insert/insert.o ./match/match.o
	gcc -o basic_example basic_example.o ./misc/misc.o ./process/process.o ./insert/insert.o ./match/match.o
	
basic_example.o : basic_example.c ./misc/misc.h ./process/process.h ./insert/insert.h ./match/match.h
	gcc -c basic_example.c	

# process module
#-------------
./process/process.o : ./process/process.c ./process/process.h
	gcc -c ./process/process.c -o ./process/process.o

# misc module
#-------------
./misc/misc.o : ./misc/misc.c ./misc/misc.h
	gcc -c ./misc/misc.c -o ./misc/misc.o

# insert module
#--------------
./insert/insert.o : ./insert/insert.c ./insert/insert.h
	gcc -c ./insert/insert.c -o ./insert/insert.o


# match module
#-------------
./match/match.o : ./match/match.c ./match/match.h
	gcc -c ./match/match.c -o ./match/match.o


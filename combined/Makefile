all : terminal

clean_all:
	rm terminal *.o


# terminal
#-------
terminal : terminal.o misc.o process.o insert.o match.o nixshell.o
	gcc -o terminal terminal.o misc.o process.o insert.o match.o nixshell.o
	
terminal.o : terminal.c ./../database/process/process.h ./../shell/nixshell/nixshell.h
	gcc -c terminal.c	

# nixshell module
#-------------
nixshell.o : ./../shell/nixshell/nixshell.c ./../shell/nixshell/nixshell.h
	gcc -c ./../shell/nixshell/nixshell.c -o nixshell.o

# process module
#-------------
process.o : ./../database/process/process.c ./../database/process/process.h
	gcc -c ./../database/process/process.c -o process.o

# misc module
#-------------
misc.o : ./../database/misc/misc.c ./../database/misc/misc.h
	gcc -c ./../database/misc/misc.c -o misc.o

# insert module
#--------------
insert.o : ./../database/insert/insert.c ./../database/insert/insert.h
	gcc -c ./../database/insert/insert.c -o insert.o


# match module
#-------------
match.o : ./../database/match/match.c ./../database/match/match.h
	gcc -c ./../database/match/match.c -o match.o


all : basic_example

clean_all:
	rm basic_example basic_example.o
	rm ./nixshell/nixshell.o

# basic_example
#--------------
basic_example : basic_example.o ./nixshell/nixshell.o
	gcc -o basic_example basic_example.o ./nixshell/nixshell.o
	
basic_example.o : basic_example.c ./nixshell/nixshell.h
	gcc -c basic_example.c

# nixshell module
#-------------
./nixshell/nixshell.o : ./nixshell/nixshell.c ./nixshell/nixshell.h
	gcc -c ./nixshell/nixshell.c -o ./nixshell/nixshell.o

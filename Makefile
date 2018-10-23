# Makefile for compiling the Shell project
# Author:  Mantas Savaniakas
# More about make files: https://www.wooster.edu/_media/files/academics/areas/computer-science/resources/makefile-tut.pdf
CC = g++
CFLAGS = -Wall
RM = rm *.o
mantas_shell: main.o shell.o
	${CC} -o main main.o shell.o
shell.o: shell.cpp general.h
	${CC} ${CFLAGS} -c shell.cpp
main.o: main.cpp general.h
	${CC} ${CFLAGS} -c main.cpp
# Clean target: removes all 
clean:
	${RM} main
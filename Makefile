CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -O3
LDFLAGS  = -g3

# Compiles the program. You just have to type "make"
hangman: main.o Hangman.o Screen.o Object.o termfuncs.o
	${CXX} ${LDFLAGS} -o hangman main.o Hangman.o Screen.o Object.o \
termfuncs.o
main.o:	main.cpp
Hangman.o:	Hangman.cpp Hangman.h Screen.h termfuncs.h
Screen.o:	Screen.cpp Screen.h Object.h termfuncs.h
Object.o:	Object.cpp Object.h termfuncs.h
termfuncs.o:	termfuncs.cpp termfuncs.h

# Cleans the current folder of all compiled files
clean:
	rm -rf hangman *.o *.dSYM

# Checks the program for possibly memory leaks
valgrind:
	valgrind ./hangman 
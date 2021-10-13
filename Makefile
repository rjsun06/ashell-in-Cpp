myshell: ashell.cpp execute.cpp parser.cpp ashell.h globals.cpp
	g++ ashell.h globals.cpp parser.cpp ashell.cpp  execute.cpp   -o ashell


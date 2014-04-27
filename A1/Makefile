all: Question.o Main.o
	g++-4.7 -std=c++11 Question.o Main.o -o Main
Question.o: Question.cpp Question.h
	g++-4.7 -std=c++11 -c Question.cpp
Main.o: Main.cpp Question.h
	g++-4.7 -std=c++11 -c Main.cpp
clean:
	rm *.o Main

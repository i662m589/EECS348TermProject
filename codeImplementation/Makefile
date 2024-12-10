APPLICATION_NAME = driver
CC = g++
CFLAGs = -c -Wall -g

all: main.o evaluator.o stack.o lexer.o parser.o
	$(CC) -o $(APPLICATION_NAME) main.o stack.o evaluator.o lexer.o parser.o -g
	make clean

evaluator.o: evaluator.cpp evaluator.h
	$(CC) $(CFLAGs) evaluator.cpp evaluator.h

lexer.o: lexer.cpp
	$(CC) $(CFLAGs) lexer.cpp

main.o: main.cpp
	$(CC) $(CFLAGs) main.cpp

parser.o: parser.cpp
	$(CC) $(CFLAGs) parser.cpp

stack.o: stack.cpp
	$(CC) $(CFLAGs) stack.cpp

clean:
	rm -f *.o
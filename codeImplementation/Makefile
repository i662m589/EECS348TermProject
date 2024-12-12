APPLICATION_NAME = driver
CC = g++
CFLAGs = -c -Wall -g

all: main.o evaluator.o stack.o lexer.o parser.o strToNum.o formatter.o
	$(CC) -o $(APPLICATION_NAME) main.o stack.o evaluator.o lexer.o parser.o strToNum.o formatter.o -g
	make clean

evaluator.o: evaluator.cpp evaluator.h
	$(CC) $(CFLAGs) evaluator.cpp evaluator.h

lexer.o: lexer.cpp lexer.h
	$(CC) $(CFLAGs) lexer.cpp lexer.h

main.o: main.cpp
	$(CC) $(CFLAGs) main.cpp

parser.o: parser.cpp parser.h
	$(CC) $(CFLAGs) parser.cpp parser.h

stack.o: stack.cpp
	$(CC) $(CFLAGs) stack.cpp

strToNum.o: strToNum.h strToNum.cpp
	$(CC) $(CFLAGs) strToNum.h strToNum.cpp

formatter.o: formatter.h formatter.cpp
	$(CC) $(CFLAGs) formatter.h formatter.cpp

clean:
	rm -f *.o
	rm -f *.gch
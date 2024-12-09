APPLICATION_NAME = driver
CC = g++
CFLAGs = -c -Wall -g

STACK = stack

all: main.o evaluator.o stack.o lexer.o parser.o
	$(CC) -o $(APPLICATION_NAME) main.o $(STACK).o evaluator.o lexer.o parser.o -g
	make clean

evaluator.o: evaluator.cpp
	$(CC) $(CFLAGs) evaluator.cpp

lexer.o: lexer.cpp
	$(CC) $(CFLAGs) lexer.cpp

main.o: main.cpp
	$(CC) $(CFLAGs) main.cpp

parser.o: parser.cpp
	$(CC) $(CFLAGs) parser.cpp

$(STACK).o: $(STACK).cpp
	$(CC) $(CFLAGs) $(STACK).cpp

clean:
	rm -f *.o
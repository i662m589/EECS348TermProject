APPLICATION_NAME = driver
CC = g++
CFLAGs = -c -Wall -g

STACK = stack

all: main.o stack.o
	$(CC) -o $(APPLICATION_NAME) main.o $(STACK).o -g

main.o: main.cpp
	$(CC) $(CFLAGs) main.cpp

$(STACK).o: $(STACK).cpp
	$(CC) $(CFLAGs) $(STACK).cpp

clean:
	rm -f *.o
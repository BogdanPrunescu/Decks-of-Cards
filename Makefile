CFLAGS = -Wall -Wextra -std=c99

build: tema1

tema1: main.o DoubleLinkedList.o deckfunctions.o
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c

DoubleLinkedList.o: DoubleLinkedList.c DoubleLinkedList.h

deckfunctions.o: deckfunctions.c deckfunctions.h

clean:
	-rm *.o

all: banking

banking: banking.c
	gcc -g banking.c -o banking -Wall -pedantic

clean:
	rm banking

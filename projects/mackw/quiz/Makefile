CFLAGS= -Wall -fpic -coverage -lm -std=c99

testme: testme.c 
	gcc -o testme testme.c -g $(CFLAGS)

run: testme
	./testme
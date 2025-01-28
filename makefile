CC=g++
CFLAGS= -c -g -Wall -std=c++17 -fpermissive
EXENAME= main

default: build/main.o build/io.o
	$(CC) build/main.o build/io.o -o $(EXENAME)

build/main.o: main.cpp io.h
	$(CC) $(CFLAGS) main.cpp -o build/main.o

build/io.o: io.cpp io.h
	$(CC) $(CFLAGS) io.cpp -o build/io.o

clean:
	rm build/*.o $(EXENAME)

run:
	./$(EXENAME)

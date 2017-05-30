CC = g++

all: main

main: main.o parser.o KFoldCV.o
	$(CC) main.o parser.o KFoldCV.o -o main
main.o: main.cpp
	$(CC) -c main.cpp -o main.o
%.o: %.cpp %.h 
	$(CC) -c $< -o $@

clean:
	rm main.o parser.o KFoldCV.o
	rm main
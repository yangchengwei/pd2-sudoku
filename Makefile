all: Sudoku.cpp test.cpp Sudoku.o test.o
	g++ -c Sudoku.cpp
	g++ -c test.cpp
	g++ -o test Sudoku.o test.o

clean:
	rm -r *.o test

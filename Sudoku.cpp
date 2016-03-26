#include <iostream>
#include <cstdio>
#include "Sudoku.h"
#define sudokuSize 81
using namespace std;

//public function
void Sudoku::giveQuestion(void){
	
}

void Sudoku::readIn(void){////////////complete
	int i, j;
	
	for (i=0 ; i<sudokuSize ; i++){
		cin>>j;
		map[i] = j;
	}

	return;
}

//void Sudoku::solve(void);

//void Sudoku::changeNum(int a, int b){

//void Sudoku::changeRow(int a, int b);

//void Sudoku::changeCol(int a, int b);

//void Sudoku::rotate(int n);

//void Sudoku::filp(int n);

//void Sudoku::transform(void);

//private function
void Sudoku::printOut(bool isAns){
	int i;
	
	if (isAns){
		for (i=0 ; i<sudokuSize ; i++){
			printf("%d%c", ans[i], (i+1)%9==0?'\n':' ');
		}
	}
	else{
		for (i=0 ; i<sudokuSize ; i++){
			printf("%d%c", map[i], (i+1)%9==0?'\n':' ');
		}
	}

	return;
}

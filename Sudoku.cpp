#include <iostream>
#include <vector>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include "Sudoku.h"
using namespace std;




///////////////////
//public function//
///////////////////


void Sudoku::giveQuestion(void){
	int i, j;

	setMap();

	change();
	
	for (i=0 ; i<sudokuSize ; i++){
		if (i%4 != 0){
			map[i] = 0;
		}
	}
	
	printOut(false);

	return;
}

void Sudoku::readIn(void){
	int i, j;
	
	for (i=0 ; i<sudokuSize ; i++){
		cin>>j;
		map[i] = j;
	}

	return;
}

void Sudoku::solve(void){
	int i, j;
	
	if (!checkLegal()){
		cout<<0<<endl;
		return;
	}

	numOfAnswer = 0;
	
	for (i=0 ; i<rowSize ; i++){
		for (j=1 ; j<=9 ; j++){
			if(checkExist(j, row[i], map) == -1){
				rowLack[i].push_back(j);
			}
		}
	}
	
	backTracking(0);

	cout<<numOfAnswer<<endl;
	
	if (numOfAnswer == 1)
		printOut(true);	

	return;
}

void Sudoku::changeNum(int a, int b){
	int i;

	for (i=0 ; i<sudokuSize ; i++){
		if (map[i] == a){
			map[i] = b;
		}
		else if (map[i] == b){
			map[i] = a;
		}
	}

	return;
}

void Sudoku::changeRow(int a, int b){
	int i;
	int buf;
	int A = a-1;
	int B = b-1;

	for (i=0 ; i<rowSize ; i++){
		buf = map[row[A][i]];
		map[row[A][i]] = map[row[B][i]];
		map[row[B][i]] = buf;
	}

	return;
}

void Sudoku::changeCol(int a, int b){
	int i;
	int buf;
	int A = a-1;
	int B = b-1;

	for (i=0 ; i<rowSize ; i++){
		buf = map[col[A][i]];
		map[col[A][i]] = map[col[B][i]];	
		map[col[B][i]] = buf;
	}

	return;
}

void Sudoku::rotate(int n){
	int i, j, k;
	int N = n%4;
	int buf[sudokuSize];

	for (k=0 ; k<N ; k++){		//n times
		for (i=0 ; i<sudokuSize ; i++){
			buf[i] = map[i];
		}
		for (i=0 ; i<rowSize ; i++){
			for (j=0 ; j<rowSize ; j++){
				map[row[i][j]] = buf[col[i][rowSize-1-j]];
			}
		}
	}

	return;
}

void Sudoku::flip(int n){
	int i, j;
	int buf[rowSize];

	if (n == 0){
		for (i=0 ; i<rowSize/2 ; i++){
			for (j=0 ; j<rowSize ; j++){
				buf[j] = map[row[i][j]];
				map[row[i][j]] = map[row[rowSize-1-i][j]];
				map[row[rowSize-1-i][j]] = buf[j];
			}
		}
	}
	else if (n == 1){
		for (i=0 ; i<rowSize/2 ; i++){
			for (j=0 ; j<rowSize ; j++){
				buf[j] = map[col[i][j]];
				map[col[i][j]] = map[col[rowSize-1-i][j]];
				map[col[rowSize-1-i][j]] = buf[j];
			}
		}
	}
	
	return;
}

void Sudoku::transform(void){
	int i;
	
	for (i=0 ; i<3 ; i++){
		change();
	}

	printOut(false);

	return;
}




////////////////////
//private function//
////////////////////


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

int Sudoku::checkExist(int n, const int* position, int* map){
	int i;
	
	for (i=0 ; i<rowSize ; i++){
		if (map[position[i]] == n){
			return i;
		}
	}
	return -1;
}

bool Sudoku::checkLegal(void){
	int i;
	int choose;
	int currentRow, currentCol, currentCell;

	for (i=0 ; i<sudokuSize ; i++){
		currentRow = i / 9;
		currentCol = i % 9;
		currentCell = (currentRow/3) * 3 + currentCol / 3;

		choose = map[i];
		map[i] = 0;

		if (choose != 0){
			if (checkExist(choose, row[currentRow], map) != -1 ||
				checkExist(choose, col[currentCol], map) != -1 ||
				checkExist(choose, cell[currentCell], map) != -1)
			{
				map[i] = choose;
				return false;		//illegal
			}
		}
		map[i] = choose;
	}

	return true;
}

void Sudoku::change(void){
	srand(time(NULL));

	changeNum(rand()%rowSize+1, rand()%rowSize+1);
	changeRow(rand()%3+1, rand()%3+1);
	changeCol(rand()%3+1, rand()%3+1);
	rotate(rand()%101);
	flip(rand()%2);

	return;
}

void Sudoku::setMap(void){
	int i;
	int modulo[81] = {
	7, 8, 9, 6, 4, 5, 1, 2, 3,
	1, 2, 3, 9, 8, 7, 4, 6, 5,
	4, 5, 6, 2, 3, 1, 7, 9, 8,
	9, 4, 8, 3, 1, 2, 5, 7, 6,
	5, 6, 7, 8, 9, 4, 2, 3, 1,
	2, 3, 1, 5, 7, 6, 9, 8, 4,
	8, 1, 5, 7, 6, 9, 3, 4, 2,
	6, 9, 4, 1, 2, 3, 8, 5, 7,
	3, 7, 2, 4, 5, 8, 6, 1, 9};


	for (i=0 ; i<sudokuSize ; i++){
		map[i] = modulo[i];
	}

	return;
}

int Sudoku::backTracking(int n){
	int N = n;
	int i;
	int currentRow, currentCol, currentCell;
	int choose, result;
	vector<int>::iterator it;		//position of begin in vector

	while (N < sudokuSize){
		
		if (map[N] == 0){
			
			currentRow = N / 9;
			currentCol = N % 9;
			currentCell = (currentRow/3) * 3 + currentCol / 3;
			
			for (i=0 ; i<rowLack[currentRow].size() ; i++){
				
				choose = rowLack[currentRow].at(i);
				
				if (checkExist(choose, col[currentCol], map) == -1 &&
					checkExist(choose, cell[currentCell], map) == -1)
				{
					it = rowLack[currentRow].begin();

					map[N] = choose;
					rowLack[currentRow].erase(it+i);
					
					result = backTracking(N+1);
					
					if (result == 2)
						return 2;

					map[N] = 0;
					rowLack[currentRow].insert(it+i, choose);
				}
			}
			return 1;		//no solution or one solution
		}
		N++;
	}

	numOfAnswer++;

	if (numOfAnswer != 1){
		return 2;
	}

	for (i=0 ; i<sudokuSize ; i++){     //assign answer
		ans[i] = map[i];
	}

	return 1;		//found a solution
}

#include <iostream>
#include <cstdio>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Sudoku.h"
using namespace std;

//public function
void Sudoku::giveQuestion(void){
	int i, j;
	srand(time(NULL));

	for (i=0 ; i<sudokuSize ; i++){
		map[i] = 0;
	}
	map[rand()%sudokuSize] = (rand()%rowSize) + 1;

	numOfAnswer = 0;		//start solve() without printOut()
	for (i=0 ; i<rowSize ; i++){
		for (j=1 ; j<=9 ; j++){
			if(checkExist(j, row[i], map) == -1){
				rowLack[i].push_back(j);
			}
		}
	}
	backTracking(0);		//end solve()

	for (i=0 ; i<sudokuSize ; i++){
		map[i] = ans[i];
	}
	for (i=0 ; i<5 ; i++){
		change();
	}
	for (i=0 ; i<sudokuSize ; i=i+2){
		map[i] = 0;
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

	for (i=0 ; i<rowSize ; i++){
		buf = map[row[a][i]];
		map[row[a][i]] = map[row[b][i]];
		map[row[b][i]] = buf;
	}

	return;
}

void Sudoku::changeCol(int a, int b){
	int i;
	int buf;

	for (i=0 ; i<rowSize ; i++){
		buf = map[col[a][i]];
		map[col[a][i]] = map[col[b][i]];
		map[col[b][i]] = buf;
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

void Sudoku::filp(int n){
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

int Sudoku::checkExist(int n, const int* position, int* map){
	int i;
	
	for (i=0 ; i<rowSize ; i++){
		if (map[position[i]] == n){
			return i;
		}
	}
	return -1;
}

void Sudoku::change(void){
	srand(time(NULL));

	changeNum(rand()%rowSize+1, rand()%rowSize+1);
	changeRow(rand()%3, rand()%3);
	changeRow(rand()%3+3, rand()%3+3);
	changeRow(rand()%3+6, rand()%3+6);
	changeCol(rand()%3, rand()%3);
	changeCol(rand()%3+3, rand()%3+3);
	changeCol(rand()%3+6, rand()%3+6);
	rotate(rand()%101);
	filp(rand()%2);

	return;
}

int Sudoku::backTracking(int n){
	int N = n;
	int i, j, k;
	int currentRow, currentCol, currentCell;
	int choose, result;
	vector<int>::iterator it;		//position of begin in vector

	for (i=N ; i<sudokuSize ; i++){
		
		if (map[i] == 0){
			
			currentRow = i / 9;
			currentCol = i % 9;
			currentCell = (currentRow/3) * 3 + currentCol / 3;
			
			for (j=0 ; j<rowLack[currentRow].size() ; j++){
				
				choose = rowLack[currentRow].at(j);
				
				if (checkExist(choose, row[currentRow], map) == -1 &&
					checkExist(choose, col[currentCol], map) == -1 &&
					checkExist(choose, cell[currentCell], map) == -1)
				{
					it = rowLack[currentRow].begin();

					map[N] = choose;
					rowLack[currentRow].erase(it+j);
					
					result = backTracking(N+1);
					
					if (result == 1){
						
						if (numOfAnswer != 0){
						   numOfAnswer++;
					   	   return 2;
						}

						numOfAnswer++;

						for (k=0 ; k<sudokuSize ; k++){		//assign answer
							ans[k] = map[k];
						}
					}
					else if (result == 2)
						return 2;

					map[N] = 0;
					rowLack[currentRow].insert(it+j, choose);
				}
			}
			return 0;		//no solution
		}
		N++;
	}
	return 1;		//found a solution
}

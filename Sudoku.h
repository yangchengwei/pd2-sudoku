#define sudokuSize 81
class Sudoku {
	public:
		void giveQuestion(void);
		void readIn(void);
		void solve(void);
		void changeNum(int a, int b);
		void changeRow(int a, int b);
		void changeCol(int a, int b);
		void rotate(int n);
		void filp(int n);
		void transform(void);
	private:
		int map[sudokuSize];
		int ans[sudokuSize];
		void printOut(bool isAns);
};

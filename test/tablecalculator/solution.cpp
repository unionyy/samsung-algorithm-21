#define MAXR		99
#define MAXC		26

#define FUNC		1000000001

#define ADD			1
#define SUB			2
#define MUL			3
#define DIV			4
#define MAX			5
#define	MIN			6
#define SUM			7

#include <iostream>
using namespace std;

typedef struct FunctionQuery {
	int func;
	int row1;
	int col1;
	int row2;
	int col2;
} FunQ;

int csts[MAXR][MAXC];
FunQ funs[MAXR][MAXC];
int C, R;

void init(int c, int r) {
	C = c;
	R = r;

	for(int i = 0; i < R; i++) {
		for(int j = 0; j < C; j++) {
			csts[i][j] = 0;
		}
	}
}

void set(int col, int row, char input[]) {
	col--;
	row--;
	if(input[0] == 'A') {
		funs[row][col].func = ADD;
	} else if(input[0] == 'S') {
		if(input[2] == 'B') funs[row][col].func = SUB;
		else  funs[row][col].func = SUM;
	} else if(input[0] == 'M') {
		if(input[1] == 'U') funs[row][col].func = MUL;
		else if(input[1] == 'A') funs[row][col].func = MAX;
		else funs[row][col].func = MIN;
	} else if(input[0] == 'D') {
		funs[row][col].func = DIV;
	} else {
		// Constant
		int pivot = 0;
		bool positive = true;
		if(input[0] == '-') {
			positive = false;
			pivot++;
		}
		int num = input[pivot] - '0';
		pivot++;
		while(input[pivot]) {
			num *= 10;
			num += input[pivot] - '0';
			pivot++;
		}
		if(positive) {
			csts[row][col] = num;
		} else {
			csts[row][col] = 0 - num;
		}
		cout << row << ", " << col << ':' << csts[row][col] << endl;
		return;
	}

	csts[row][col] = FUNC;

	funs[row][col].col1 = input[4] - 'A';
	int pivot = 5;
	int num = input[pivot] - '1';
	pivot++;
	if(input[pivot] != ',') {
		num *= 10;
		num += input[pivot] - '1';
		pivot++;
	}
	funs[row][col].row1 = num;
	pivot++;

	funs[row][col].col2 = input[pivot] - 'A';
	pivot++;
	num = input[pivot] - '1';
	pivot++;
	if(input[pivot] != ')') {
		num *= 10;
		num += input[pivot] - '1';
		pivot++;
	}
	funs[row][col].row2 = num;
	
	cout << row << ", " << col << ':' << csts[row][col] << endl;
	return;
}

int solve(int row, int col) {
	if(csts[row][col] != FUNC) {
		return csts[row][col];
	}

	int cst1 = solve(funs[row][col].row1, funs[row][col].col1);
	int cst2 = solve(funs[row][col].row2, funs[row][col].col2);

	int ans;
	switch (funs[row][col].func)
	{
	case ADD:
		ans = cst1 + cst2;
		break;
	case SUB:
		ans = cst1 - cst2;
		break;
	case MUL:
		ans = cst1 * cst2;
		break;
	case DIV:
		ans = cst1 / cst2;
		break;
	case MAX:
		ans = cst1;
		for(int i = funs[row][col].row1; i < funs[row][col].row2 + 1; i++) {
			for(int j = funs[row][col].col1; j < funs[row][col].col2 + 1; j++) {
				if(solve(i, j) > ans) ans = csts[i][j];
			}
		}
		break;
	case MIN:
		ans = cst1;
		for(int i = funs[row][col].row1; i < funs[row][col].row2 + 1; i++) {
			for(int j = funs[row][col].col1; j < funs[row][col].col2 + 1; j++) {
				if(solve(i, j) < ans) ans = csts[i][j];
			}
		}
		break;
	case SUM:
		ans = 0;
		for(int i = funs[row][col].row1; i < funs[row][col].row2 + 1; i++) {
			for(int j = funs[row][col].col1; j < funs[row][col].col2 + 1; j++) {
				ans += solve(i, j);
			}
		}
		break;
	default:
		cout << "error";
		ans = 0;
		break;
	}

	csts[row][col] = ans;

	return ans;
}

void update(int value[MAXR][MAXC]) {
	for(int i = 0; i < R; i++) {
		for(int j = 0; j < C; j++) {
			if(csts[i][j] == FUNC) cout << 'F' << "\t";
			else cout << csts[i][j] << '\t';
		}
		cout << endl;
		cout << endl;
	}
	cout << endl << endl;
	for(int i = 0; i < R; i++) {
		for(int j = 0; j < C; j++) {
			value[i][j] = solve(i, j);
			cout << value[i][j] << '\t';
		}
		cout << endl;
		cout << endl;
	}
	return;
}
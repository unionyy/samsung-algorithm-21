#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <iostream>
using namespace std;

#define MAXR		99
#define MAXC		26

#define MAXL		100

extern void init(int C, int R);
extern void set(int col, int row, char input[]);
extern void update(int value[MAXR][MAXC]);

#define INIT		100
#define SET			200
#define UPDATE		300

static int R;
static int C;

static int gethash(int value[MAXR][MAXC]) {
	int ret = 0;

	for (int r = 0; r < R; ++r)
	for (int c = 0; c < C; ++c)
		ret = (ret * 7 + value[r][c]) & 0x7fffffff;

	return ret;
}

static bool run() {
	int  Q;
	bool okay = true;

	scanf("%d", &Q);

	for (int q = 0; q < Q; ++q) {
		int cmd, row, col;
		int userhash, answerhash;

		char input[MAXL];
		int value[MAXR][MAXC];

		scanf("%d", &cmd);

		switch(cmd) {
		case INIT:
			scanf("%d %d", &C, &R);
			if (okay) init(C, R);
			break;
		case SET:
			scanf("%d %d %s", &col, &row, input);
			if (okay) set(col, row, input);
			break;
		case UPDATE:
			scanf("%d", &answerhash);
			if (okay) {
				update(value);
				userhash = gethash(value);
				if (answerhash != userhash)
					okay = false;

				if (okay)
					cout << "okay\n";
				else
					cout << userhash << "\n";
			}
			break;
		default:
			break;
		}
	}
	return okay && Q > 0;
}

int main() {
	int TC;

    freopen("sample_input.txt", "r", stdin);

	setbuf(stdout, NULL);
    scanf("%d", &TC);

	int totalscore = 0;
    for (int testcase = 1; testcase <= TC; ++testcase) {
		int score = run() ? 100 : 0;
		printf("#%d %d\n", testcase, score);
		totalscore += score;
    }
	printf("total score = %d\n", totalscore / TC);
    return 0;
}
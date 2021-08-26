#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

extern void init(int, char[][20], char[][100], int[]);
extern void priceChange(char[], char[]);
extern int daySurvivable(char[]);

static int run()
{
	int ret_val = 1;
	int N, Q, mDuration[50] = {};
	char mName[50][20] = {}, mPrice[50][100] = {};
	scanf("%d %d", &N, &Q);

	for (int i = 0; i < N; ++i) {
		scanf("%s %s %d", mName[i], mPrice[i], &mDuration[i]);
	}

	init(N, mName, mPrice, mDuration);

	for (int i = 0; i < Q; ++i) {
		int type;
		scanf("%d", &type);
		if (type == 1) {
			char name[20] = {}, price[100] = {};

			scanf("%s %s", name, price);
			priceChange(name, price);
		}
		else if (type == 2) {
			char money[100] = {};

			scanf("%s", money);

			int user, answer;
			user = daySurvivable(money);
			scanf("%d", &answer);

			if (user != answer) {
				ret_val = 0;
				printf("%d: user: %d, answer: %d\n", i, user, answer);
			}
		}
	}

	return ret_val;
}

int main()
{
	setbuf(stdout, NULL);
	freopen("sample_input.txt", "r", stdin);

	int T, score;
	scanf("%d%d", &T, &score);

	for (int tc = 1; tc <= T; tc++) {
		if (run() == 1)
			printf("#%d %d\n", tc, score);
		else
			printf("#%d 0\n", tc);
	}

	return 0;
}
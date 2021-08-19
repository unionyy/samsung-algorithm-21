#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include "solution.cpp"

#define INPUTWORD	(100)
#define RECOMMEND	(200)
#define BANWORD		(300)

extern void init();
extern void inputWord(char mWord[20]);
extern int recommend(char mUser[20], char mAnswer[20]);
extern void banWord(char mWord[20]);



static int run()
{
	int ret_val = 1;
	int type, len;
	char mWord[20] = {}, mAnswer[20] = {}, ans[20] = {};

	init();

	int N;
	scanf("%d", &N);

	for (int i = 0; i < N; ++i) {
		scanf("%d %s", &type, mWord);

		switch (type) {
		case INPUTWORD:
			inputWord(mWord);
			break;
		case RECOMMEND:
			len = recommend(mWord, mAnswer);
			scanf("%s", ans);

			if (len != mstrlen(ans))
				{ret_val = 0;
				printf("!");}
			if (mstrcmp(ans, mAnswer) != 0)
				{ret_val = 0;
				printf("@");}
			if(ret_val == 0) printf("%d: %s:  %s, %s\n", ret_val, mWord, ans, mAnswer);
			break;
		case BANWORD:
			banWord(mWord);
			break;
		default:
			ret_val = 0;
			break;
		}
	}

	return ret_val;
}

int main()
{
	setbuf(stdout, NULL);
	freopen("sample_input.txt", "r", stdin);

	int T, MARK;
	scanf("%d %d", &T, &MARK);

	for (int tc = 1; tc <= T; tc++) {
		int score = run() ? MARK : 0;
		printf("#%d %d\n", tc, score);
	}

	return 0;
}
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include "solution.cpp"

extern void init(int n, char init_string[]);
extern int change(char string_A[], char string_B[]);
extern void result(char ret[]);

static int seed = 5;  // seed can be changed
static int pseudo_rand(void)
{
	seed = seed * 214013 + 2531011;
	return (seed >> 16) & 0x7FFF;
}

#define MAXL (50005)
#define DUMMY_LEN (5959)

static int init_string_len = 0, char_type = 0, query_cnt = 0;
static char dummy1[DUMMY_LEN];
static char init_string[MAXL];
static char dummy2[DUMMY_LEN];
static char result_string[MAXL];
static char dummy3[DUMMY_LEN];
static char user_ans_string[MAXL];
static char dummy4[DUMMY_LEN];
static char string_A[4], string_B[4];


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

int main() {
	setbuf(stdout, NULL);
	freopen("sample_input.txt", "r", stdin);
	int T;
	scanf("%d", &T);
	int total_score = 0;
	for (int TC = 1; TC <= T; TC++) {
		int score = 100;
		scanf("%d%d%d%d", &seed, &init_string_len, &char_type, &query_cnt);
		
		for (int i = 0; i < init_string_len; i++)
		{
			init_string[i] = pseudo_rand() % char_type + 'a';
		}
		init_string[init_string_len] = '\0';

		init(init_string_len, init_string);

		string_A[3] = string_B[3] = '\0';
		for (int i = 0; i < query_cnt; i++)
		{
			for (int k = 0; k < 3; k++)
			{
				string_A[k] = pseudo_rand() % char_type + 'a';
				string_B[k] = pseudo_rand() % char_type + 'a';
			}
			int user_ans = change(string_A, string_B);
			int ans;
			scanf("%d", &ans);

			if (ans != user_ans)
			{
				score = 0;
			}
		}

		result(user_ans_string);
		scanf("%s", result_string);
        printf("%s\n", result_string);
        printf("%s\n", user_ans_string);

		for (int i = 0; i < init_string_len; i++)
		{
			if (result_string[i] != user_ans_string[i])
			{
				score = 0;
				break;
			}
		}

		total_score += score;
		printf("#%d %d\n", TC, score);
	}
	printf("Total score : %d\n", total_score/T);

	return 0;
}
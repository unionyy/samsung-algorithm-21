#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include "solution.cpp"

#define CMD_INIT		100
#define CMD_ADD			200
#define CMD_MOVETYPE	300
#define CMD_MOVENAME	400
#define CMD_DELETENAME	500
#define CMD_COUNTBOOK	600

#define MAX_N			5

#define MAX_NAME_LEN	7
#define MAX_TAG_LEN		4

extern void init(int M);
extern void add(char mName[MAX_NAME_LEN], int mTypeNum, char mTypes[MAX_N][MAX_TAG_LEN], int mSection);
extern int  moveType(char mType[MAX_TAG_LEN], int mFrom, int mTo);
extern void moveName(char mName[MAX_NAME_LEN], int mSection);
extern void deleteName(char mName[MAX_NAME_LEN]);
extern int  countBook(int mTypeNum, char mTypes[MAX_N][MAX_TAG_LEN], int mSection);

extern void showBooks();

static bool run()
{
	int  Q;
	int  cmd, M, mTypeNum, mSection, mFrom, mTo;
	char mName[MAX_NAME_LEN], mType[MAX_TAG_LEN], mTypes[MAX_N][MAX_TAG_LEN];
	
	int  ret, ans;
	
	scanf("%d", &Q);
		
	bool okay = false;
	
	for (int q = 0; q <= Q; ++q)
	{
		scanf("%d", &cmd);

		switch(cmd)
		{
		case CMD_INIT:
			scanf("%d", &M);
			init(M);
			okay = true;
			break;
		case CMD_ADD:
			scanf("%s %d", mName, &mTypeNum);
			for (int i = 0; i < mTypeNum; ++i)
				scanf("%s", mTypes[i]);
			scanf("%d", &mSection);
			if (okay)
				add(mName, mTypeNum, mTypes, mSection);
			break;
		case CMD_MOVETYPE:
			scanf("%s %d %d", mType, &mFrom, &mTo);
			if (okay)
				ret = moveType(mType, mFrom, mTo);
			scanf("%d", &ans);
			if (ret != ans)
				okay = false;
			break;
		case CMD_MOVENAME:
			scanf("%s %d", mName, &mSection);
			if (okay)
				moveName(mName, mSection);
			break;
		case CMD_DELETENAME:
			scanf("%s", mName);
			if (okay)
				deleteName(mName);
			break;
		case CMD_COUNTBOOK:
			scanf("%d", &mTypeNum);
			for (int i = 0; i < mTypeNum; ++i)
				scanf("%s", mTypes[i]);
			scanf("%d", &mSection);
			if (okay)
				ret = countBook(mTypeNum, mTypes, mSection);
			scanf("%d", &ans);
			if (ret != ans)
				okay = false;
			break;
		}

        showBooks();
        if(!okay) {
            printf("fail: %d, %d\n", ret, ans);
            return okay;
        }
	}
	
	return okay;
}

int main()
{
	setbuf(stdout, NULL);
	freopen("sample_input.txt", "r", stdin);

	int T, MARK;
	scanf("%d %d", &T, &MARK);

	for (int tc = 1; tc <= T; tc++)
	{
		int score = run() ? MARK : 0;
		
		printf("#%d %d\n", tc, score);
	}

	return 0;
}
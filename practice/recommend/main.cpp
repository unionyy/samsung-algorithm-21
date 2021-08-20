#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define	MAXL			5
#define MAXF			10

extern void init(int N);
extern void add(int id, int F, int ids[MAXF]);
extern void del(int id1, int id2);
extern int  recommend(int id, int list[MAXL]);

#define INIT			1
#define ADD				2
#define DEL				3
#define RECOMMEND		4

static int N, M;

static bool run()
{
	int cmd;
	int id, F, ids[MAXF];
	int id1, id2;
	int len, len_a;
	int list[MAXL], list_a[MAXL];

	bool okay;

	okay = false;

	scanf("%d", &M);

	for (int k = 0; k < M; ++k)
	{
		scanf("%d", &cmd);
		switch (cmd)
		{
		case INIT:
			scanf("%d", &N);
			init(N);
			okay = true;
			break;
		case ADD:
			scanf("%d %d", &id, &F);
			for (int i = 0; i < F; ++i)
				scanf("%d", &ids[i]);
			if (okay)
				add(id, F, ids);
			/*printf("Add: %d, ", id);
			for (int l = 0; l < F; l++) printf("%d ", ids[l]);
			printf("\n");*/
			break;
		case DEL:
			scanf("%d %d", &id1, &id2);
			if (okay)
				del(id1, id2);
			//printf("del: %d %d\n", id1, id2);
			break;
		case RECOMMEND:
			scanf("%d %d", &id, &len_a);
			for (int i = 0; i < len_a; ++i)
				scanf("%d", &list_a[i]);
			if (okay)
			{
				len = recommend(id, list);
				if (len != len_a)
					okay = false;

				for (int i = 0; okay && i < len_a; ++i)
					if (list[i] != list_a[i])
						okay = false;
				/*printf("rec: %d\n", id);
				for (int l = 0; l < len_a; l++) printf("%d ", list_a[l]);
				printf("\n");
				for (int l = 0; l < len_a; l++) printf("%d ", list[l]);
				printf("\n");*/
			}
			break;
		}
	}

	return okay;
}

int main()
{
	int TC, MARK;

	freopen("sample_input.txt", "r", stdin);

	setbuf(stdout, NULL);
	scanf("%d %d", &TC, &MARK);

	for (int testcase = 1; testcase <= TC; ++testcase)
	{
		int score = run() ? MARK : 0;
		printf("#%d %d\n", testcase, score);
	}

	return 0;
}
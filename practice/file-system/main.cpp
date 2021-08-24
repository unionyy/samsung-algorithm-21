#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include "solution.cpp"

void init();
void createUser(char userName[], char groupName[]);
int createDirectory(char userName[], char path[], char directoryName[], int permission);
int createFile(char userName[], char path[], char fileName[], char fileExt[]);
int find(char userName[], char pattern[]);

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

static int run(int Ans)
{
    int n;
    scanf("%d", &n);
    init();

    char userName[8];
    char groupName[8];
    char path[500];
    char directoryName[8];
    int permission;
    int expectedAnswer;
    char fileName[8];
    char fileExt[8];
    char pattern[500];

    for(int i=0; i<n; i++)
    {
        int type;
        scanf("%d", &type);

        if(type == 1)
        {
            scanf("%s %s", userName, groupName);

            createUser(userName, groupName);
        }
        else if(type == 2)
        {
            scanf("%s %s %s %d", userName, path, directoryName, &permission);

            int userAnswer = createDirectory(userName, path, directoryName, permission);
            scanf("%d", &expectedAnswer);
            printf("%d: %d %d\n", i, userAnswer, expectedAnswer);
            if(userAnswer != expectedAnswer)
                Ans = 0;
        }
        else if(type == 3)
        {
            scanf("%s %s %s %s", userName, path, fileName, fileExt);

            int userAnswer = createFile(userName, path, fileName, fileExt);
            scanf("%d", &expectedAnswer);
            printf("%d: %d %d\n", i, userAnswer, expectedAnswer);
            if(userAnswer != expectedAnswer)
                Ans = 0;
        }
        else if(type == 4)
        {
            scanf("%s %s", userName, pattern);

            int userAnswer = find(userName, pattern);
            scanf("%d", &expectedAnswer);
            printf("%d: %d %d\n", i, userAnswer, expectedAnswer);
            if(userAnswer != expectedAnswer)
                Ans = 0;
        }
    }

    return Ans;
}

int main()
{
    setbuf(stdout, NULL);
    freopen("sample_input.txt", "r", stdin);

    int T, Ans;
    scanf("%d %d", &T, &Ans);

    for (int tc = 1; tc <= T; tc++)
    {
        printf("#%d %d\n", tc, run(Ans));
    }

    return 0;
}
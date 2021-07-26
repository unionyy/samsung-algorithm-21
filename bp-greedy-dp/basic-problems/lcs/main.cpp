#include<iostream>

using namespace std;

char A[1000], B[1000];

int dp[1000][1000];

int LCS(int a, int b) {
    if(a < 0 || b < 0) return 0;

    if(dp[a][b] != -1) return dp[a][b];

    int rev;

    if(A[a] == B[b]) rev =  LCS(a - 1, b - 1) + 1;
    else {
        int caseA = LCS(a, b - 1);
        int caseB = LCS(a - 1, b);
        if(caseA > caseB) rev =  caseA;
        else rev =  caseB;
    }
    dp[a][b] = rev;
    return rev;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	cin>>T;
	for(test_case = 1; test_case <= T; ++test_case)
	{
        cin >> A >> B;
        int lenA = 0, lenB = 0;

        while(A[lenA]) lenA++;
        while(B[lenB]) lenB++;

        for(int i = 0; i < lenA; i++) {
            for(int j = 0; j < lenB; j++) dp[i][j] = -1;
        }

        cout << '#' << test_case << ' ' << LCS(lenA - 1, lenB - 1) << endl;
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
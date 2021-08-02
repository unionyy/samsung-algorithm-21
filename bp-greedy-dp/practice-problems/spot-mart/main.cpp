#include <iostream>
using namespace std;

#define MAXN 3000
#define MAXM 100

int N, M;
int A[MAXN], B[MAXM];
int dp[MAXN][MAXM][MAXM][2];

void QuickSort(int l, int r) {
    if(l >= r) return;
    int pivotL = l;
    int pivotR = r;
    int m = (l + r) / 2;
    while(true) {
        while(pivotL < m && B[pivotL] <= B[m]) pivotL++;
        while(pivotR > m && B[pivotR] >= B[m]) pivotR--;
        if(pivotL == pivotR) break;
        int tmp = B[pivotL];
        B[pivotL] = B[pivotR];
        B[pivotR] = tmp;
        if(m == pivotL) m = pivotR;
        else if(m == pivotR) m = pivotL;
    }
    QuickSort(l, m - 1);
    QuickSort(m + 1, r);
    return;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    for(int tc = 1; tc <= T; tc++) {
        cin >> N;
        for(int n = 0; n < N; n++) cin >> A[n];
        cin >> M;
        for(int m = 0; m < M; m++) cin >> B[m];
        for(int n = 0; n < N; n++) for(int m = 0; m < M; m++)
            for(int m2 = 0; m2 < M; m2++) {
                dp[n][m][m2][0] = -1;
                dp[n][m][m2][1] = -1;
            }
        QuickSort(0, M - 1);
    }
}
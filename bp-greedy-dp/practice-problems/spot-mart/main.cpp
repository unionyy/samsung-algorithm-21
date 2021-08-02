#include <iostream>
using namespace std;

#define MAXN 3000
#define MAXM 100

int N, M;
int A[MAXN], B[MAXM];
int dp[MAXN + 1][MAXM + 1][MAXM + 1][2];

int Find(int idx, int l, int r, int take) {
    if(dp[idx][l][r][take] != -1) return dp[idx][l][r][take];
    if(idx == 0 && l == 0) return dp[idx][l][r][take] = 0;
    if(l + r > M) return dp[idx][l][r][take] = 0;

    int val;
    if(take == 1) {
        int f1 = 0, f2 = 0;
        if(idx > 0) f1 = Find(idx - 1, l, r, 0) + A[idx - 1];
        if(l > 0) f2 = Find(idx, l - 1, r, 0) + B[M - l];
        val = (f1 > f2) ? f1 : f2;
    } else {
        int f1 = 0, f2 = 0, f3 = 0, f4 = 0;
        if(idx > 0) {
            f1 = Find(idx - 1, l, r, 0);
            f2 = Find(idx - 1, l, r, 1);
        }
        if(r > 0) {
            f3 = Find(idx, l, r - 1, 0);
            f4 = Find(idx, l, r - 1, 1);
        }
        val = (f1 > f2) ? f1 : f2;
        if(f3 > val) val = f3;
        if(f4 > val) val = f4;
    }
    return dp[idx][l][r][take] = val;
}

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
    // freopen("input.txt", "r", stdin);

    int T;
    cin >> T;
    for(int tc = 1; tc <= T; tc++) {
        cin >> N;
        for(int n = 0; n < N; n++) cin >> A[n];
        cin >> M;
        for(int m = 0; m < M; m++) cin >> B[m];
        for(int n = 0; n <= N; n++) for(int m = 0; m <= M; m++)
            for(int m2 = 0; m2 <= M; m2++) {
                dp[n][m][m2][0] = -1;
                dp[n][m][m2][1] = -1;
            }
        QuickSort(0, M - 1);

        int max = 0;
        for(int l = 0; l <= M; l++) {
            int r = M - l;
            if(Find(N, l, r, 0) > max) max = dp[N][l][r][0];
            if(Find(N, l, r, 1) > max) max = dp[N][l][r][1];
        }
        cout << '#' << tc << ' ' << max << '\n';
    }
}
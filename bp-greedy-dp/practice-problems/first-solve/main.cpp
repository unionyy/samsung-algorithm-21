#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 1000
#define MAXF 1000000
#define INF 2000001

int N;
int ss[MAXN];
int fs[MAXN];

int idx[MAXN];

int dp[MAXN + 1][MAXN + 1];

void QuickSort(int l, int r) {
    if(l >= r) return;
    int m = (l + r) / 2;
    int pivotL = l;
    int pivotR = r;
    while(true) {
        while(pivotL < m && fs[idx[pivotL]] <= fs[idx[m]]) pivotL++;
        while(pivotR > m && fs[idx[pivotR]] >= fs[idx[m]]) pivotR--;
        if(pivotL == pivotR) break;
        int tmp = idx[pivotL];
        idx[pivotL] = idx[pivotR];
        idx[pivotR] = tmp;
        if(pivotL == m) m = pivotR;
        else if(pivotR == m) m = pivotL;
    }
    
    QuickSort(l, m - 1);
    QuickSort(m + 1, r);
    return;
}

int FindD(int _idx, int solved) {
    if(dp[_idx][solved] != -1) return dp[_idx][solved];
    if(solved == 0) {
        dp[_idx][solved] = 0;
        return 0;
    }
    if(_idx == 0) {
        dp[_idx][solved] = INF;
        return INF;
    }
    int min = FindD(_idx - 1, solved);
    int b = FindD(_idx - 1, solved - 1) + ss[idx[_idx - 1]];
    if(min > b) min = b;
    if(min > fs[idx[_idx - 1]]) min = INF;
    dp[_idx][solved] = min;
    return min;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    //freopen("s_input.txt", "r", stdin);

    int T;
    cin >> T;
    for(int tc = 1; tc <= T; tc++) {
        N;
        cin >> N;
        for(int n = 0; n < N; n++) {
            cin >> ss[n] >> fs[n];
            idx[n] = n;
        }
        QuickSort(0, N - 1);

        for(int i = 0; i <= N; i++)
            for(int j = 0; j <= N; j++) dp[i][j] = -1;
        for(int i = 0; i <= N; i++) FindD(N, i);
        int cnt = N;
        while(dp[N][cnt] == INF) cnt--;

        cout << '#' << tc << ' ' << cnt << "\n";
    }
}

#include <iostream>
using namespace std;

#define MAXN 50000
#define MAXM 200000

int N, M;

struct Edge {
    int start;
    int end;
    int cost;
} edges[MAXM];

int parents[MAXN];

int updateQ[MAXN];

void QuickSort(int l, int r) {
    if(l >= r) return;
    int m = (l + r) / 2;
    int pivotL = l;
    int pivotR = r;
    while(true) {
        while(edges[pivotL].cost <= edges[m].cost && pivotL < m) pivotL++;
        while(edges[pivotR].cost >= edges[m].cost && pivotR > m) pivotR--;
        if(pivotR == pivotL) break;
        Edge tmp = edges[pivotL];
        edges[pivotL] = edges[pivotR];
        edges[pivotR] = tmp;
        if(pivotL == m) m = pivotR;
        else if(pivotR == m) m = pivotL;
    }
    QuickSort(l, m - 1);
    QuickSort(m + 1, r);

    return;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("input.txt", "r", stdin);

    int T;
    cin >> T;
    for(int tc = 1; tc <= T; tc++) {
        cin >> N >> M;
        for(int n = 0; n < N; n++) parents[n] = n;
        for(int m = 0; m < M; m++) {
            cin >> edges[m].start >> edges[m].end >> edges[m].cost;
            edges[m].start--;
            edges[m].end--;
        }
        QuickSort(0, M - 1);

        int sum = 0;
        for(int m = 0; m < M; m++) {
            int s = edges[m].start;
            int e = edges[m].end;
            int c = edges[m].cost;

            int sp = s;
            int ep = e;
            int updateCnt = 0;
            while(sp != parents[sp]) {
                updateQ[updateCnt++] = sp;
                sp = parents[sp];
            }
             for(int i = 0; i < updateCnt; i++)
                 parents[updateQ[i]] = sp;

            updateCnt = 0;
            while(ep != parents[ep]) {
                updateQ[updateCnt++] = ep;
                ep = parents[ep];
            }
             for(int i = 0; i < updateCnt; i++)
                 parents[updateQ[i]] = sp;

            if(sp == ep) continue;

            sum += c;
            parents[ep] = sp;
        }

        cout << '#' << tc << ' ' << sum << "\n";
    } 
    return 0;
}
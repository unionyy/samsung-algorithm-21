#include <iostream>
using namespace std;

#define MAXN 1000

int N, E;

struct Edge {
    int start;
    int end;
    long long dist;
} edges[MAXN * MAXN];

int locs[MAXN][2];
bool connects[MAXN][MAXN];

void QuickSort(int l, int r) {
    if(l >= r) return;
    int m = (l + r) / 2;

    int pivot = l;
    int pivot2 = r;
    while(pivot < pivot2) {
        while(pivot < m && edges[pivot].dist <= edges[m].dist) pivot++;
        while(pivot2 > m && edges[pivot2].dist >= edges[m].dist) pivot2--;
        Edge tmp = edges[pivot];
        edges[pivot] = edges[pivot2];
        edges[pivot2] = tmp;
        if(m == pivot) m = pivot2;
        else if(m == pivot2) m = pivot;
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
        cin >> N;
        E = 0;
        for(int i = 0; i < N; i++) cin >> locs[i][0];
        for(int i = 0; i < N; i++) cin >> locs[i][1];
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < i; j++) {
                long long dist = locs[i][0] - locs[j][0];
                long long dist2 = locs[i][1] - locs[j][1];
                dist = dist * dist + dist2 * dist2;
                edges[E].start = i;
                edges[E].end = j;
                edges[E].dist = dist;
                E++;
            }
        }
        double EE;
        cin >> EE;
        QuickSort(0, E - 1);
        int cnt = 0;

        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                if(i == j) connects[i][j] = true;
                else connects[i][j] = false;
            }
        }

        long long sum = 0;
        double sum2 = 0;
        for(int i = 0; i < E; i++) {
            int s = edges[i].start;
            int e = edges[i].end;
            long long d = edges[i].dist;
            if(connects[s][e]) continue;
            double val = d * EE;
            long long nval = val;
            sum += nval;
            sum2 += val - nval;
            for(int j = 0; j < N; j++) {
                if(connects[s][j]) {
                    for(int k = 0; k < N; k++) {
                        if(connects[e][k]) {
                            connects[j][k] = true;
                            connects[k][j] = true;
                        }
                    }
                }
            }
        }
        sum2 += 0.5;
        sum += sum2;
        cout << '#' << tc << ' ' << sum << "\n";
    }
    return 0;
}
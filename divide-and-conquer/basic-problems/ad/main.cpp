#include <iostream>
using namespace std;

int se[1000000][2];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("input.txt", "r", stdin);

    int T;
    cin >> T;
    for(int tc = 1; tc <= T; tc++) {
        int L, N;
        cin >> L >> N;
        int max = 0;
        int cur = 0;
        int front = 0;
        int back = 0;
        int pivot = 0;
        for(int n = 0; n < N; n++) {
            int s, e;
            cin >> s >> e;
            se[back][0] = s;
            se[back][1] = e;
            back++;
            cur += e - s;
            int pivotN = e - L;
            while(pivot < pivotN) {
                if(se[front][0] > pivot) {
                    pivot = se[front][0];
                } else if(se[front][1] < pivotN) {
                    cur -= se[front][1] - pivot;
                    front++;
                    pivot = se[front][0];
                } else {
                    cur -= pivotN - pivot;
                    pivot = pivotN;
                }
            }
            if(cur > max) max = cur;
            if(pivotN > pivot) pivot = pivotN;
        }
        cout << '#' << tc << ' ' << max << "\n";
    }
}
#include <iostream>
using namespace std;

#define MAXN 200000

int W[MAXN], S[MAXN];
int N, K;

bool Verify(int val) {
    int pivot = -1;
    for(int k = 0; k < K; k++) {
        for(int s = 0; s < S[k]; s++) {
            pivot++;
            if(pivot == N) return false;
            if(W[pivot] > val) {
                k--;
                break;
            }
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for(int tc = 1; tc <= T; tc++) {
        cin >> N >> K;
        for(int n = 0; n < N; n++) cin >> W[n];
        for(int k = 0; k < K; k++) cin >> S[k];

        int l = 0, r = 200000;
        while(l < r) {
            int m = (l + r) / 2;
            if(Verify(m)) r = m;
            else l = m + 1;
        }
        cout << '#' << tc << ' ' << r << '\n';
    }
    return 0;
}
#include <iostream>
using namespace std;

#define MAXN 100000

int N, K;

int nums[MAXN];
int numsTmp[MAXN];

bool Verify(int val) {
    int k = K;
    for(int n = 0; n < N; n++) {
        int del = 0;
        if(n > 0) del = nums[n] - numsTmp[n - 1];
        if(n < N - 1) {
            int tmp = nums[n] - nums[n + 1];
            if(tmp > del) del = tmp;
        }
        if(del > val) {
            numsTmp[n] = nums[n] - del + val;
            k -= del - val;
        } else numsTmp[n] = nums[n];
        if(k < 0) return false;
    }
    for(int n = N - 1; n >= 0; n--) {
        int del = 0;
        if(n > 0) del = numsTmp[n] - numsTmp[n - 1];
        if(n < N - 1) {
            int tmp = numsTmp[n] - numsTmp[n + 1];
            if(tmp > del) del = tmp;
        }
        if(del > val) {
            numsTmp[n] = numsTmp[n] - del + val;
            k -= del - val;
        }
        if(k < 0) return false;
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
        for(int n = 0; n < N; n++) cin >> nums[n];

        int max = 0;
        for(int n = 0; n < N - 1; n++) {
            int del = nums[n] - nums[n+1];
            if(del < 0) del = 0 - del;
            if(max < del) max = del;
        }

        int l = 0, r = max;
        while(l < r) {
            int m = (l + r) / 2;
            if(Verify(m)) r = m;
            else l = m + 1;
        }
        cout << '#' << tc << ' ' << r << '\n';
    }
    return 0;
}
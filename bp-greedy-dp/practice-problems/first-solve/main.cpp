#include <iostream>
using namespace std;

#define MAXN 1000
#define MAXF 1000000

int N;
int ss[MAXN];
int fs[MAXN];
int dels[MAXN];

int FindMax(int time) {
    int max = -1;
    int idx = -1;
    for(int n = 0; n < N; n++) {
        int del;
        if(dels[n] < 0) continue;
        if(time > fs[n]) del = fs[n] - ss[n];
        else del = time - ss[n];
        if(del > max) {
            max = del;
            idx = n;
        } else if(del == max && ss[idx] < ss[n]) {
            max = del;
            idx = n;
        }
    }
    dels[idx] = max;
    return idx;
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
            dels[n] = fs[n] - ss[n];
        }

        int time = MAXF;
        int cnt = 0;
        while(true) {
            int idx = FindMax(time);
            if(idx < 0) break;
            cnt++;
            time = dels[idx];
            dels[idx] = -1;
        }

        cout << '#' << tc << ' ' << cnt << "\n";
    }
}

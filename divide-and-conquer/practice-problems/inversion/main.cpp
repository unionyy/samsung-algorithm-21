#include <iostream>
using namespace std;

#define MAXN 100000

int N;

int nums[MAXN];

bool check[MAXN];
int cp[MAXN >> 10];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("input.txt", "r", stdin);

    int T;
    cin >> T;
    for(int tc = 1; tc <= T; tc++) {
        cin >> N;
        for(int n = 0; n < N; n++) {
            cin >> nums[N - n - 1];
            nums[N - n - 1]--;
            check[n] = false;
        }

        for(int i = 0; i < N >> 10; i++) cp[i] = 0;
        long long cnt = 0;
        for(int n = 0; n < N; n++) {
            int p = nums[n] >> 10;
            for(int i = p << 10; i < nums[n]; i++) {
                if(check[i]) cnt++;
            }
            cp[p]++;
            check[nums[n]] = true;
            while(p > 0) {
                p--;
                cnt += cp[p];
            }
        }
        cout << '#' << tc << ' ' << cnt << '\n';
    }
    return 0;
}